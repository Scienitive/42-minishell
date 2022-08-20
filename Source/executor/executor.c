/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:02:06 by alyasar           #+#    #+#             */
/*   Updated: 2022/08/09 12:54:41 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	try_path_helper(t_gen *gen, int cmd_i, char *path_line)
{
	char	*path;
	int		i;

	i = 0;
	while (1)
	{
		path = fill_path(path_line, i);
		if (path[0] == '\0')
		{
			free(path);
			break ;
		}
		path = ft_strjoinf(path, "/");
		path = ft_strjoinf(path, gen->command[cmd_i].cmd);
		if (access(path, X_OK) == 0)
		{
			gen->command[cmd_i].cmd = path;
			break ;
		}
		else
			free(path);
		i++;
	}
}

void	try_path(t_gen *gen, int cmd_i)
{
	int		i;
	char	*path_line;

	path_line = NULL;
	i = -1;
	while (++i < get_string_arr_len(gen->envp))
	{
		if (ft_strncmpf(gen->envp[i], "PATH=", 5) == 0)
		{
			path_line = gen->envp[i];
			break ;
		}
	}
	if (path_line)
		try_path_helper(gen, cmd_i, path_line);
}

void	child_process(t_gen *gen, int i)
{
	restore_sigint(gen);
	dup2(gen->command[i].descriptor.in, STDIN_FILENO);
	if (gen->command[i].descriptor.in != STDIN_FILENO)
		close(gen->command[i].descriptor.in);
	dup2(gen->command[i].descriptor.out, STDOUT_FILENO);
	if (gen->command[i].descriptor.out != STDOUT_FILENO)
		close(gen->command[i].descriptor.out);
	if (!ft_strcont(gen->command[i].cmd, '/'))
		try_path(gen, i);
	if (execve(gen->command[i].cmd, gen->command[i].args, gen->envp)
		== -1)
	{
		if (errno == EACCES || errno == EISDIR)
			print_error("command is not executable.", gen, 126, 0);
		else
			print_error("command not found.", gen, 127, 0);
	}
	close(gen->command[i].descriptor.out);
	free_all_exit(gen);
}

t_bool	is_builtin(char *cmd, char **args, t_gen *gen, int fdout)
{
	if (ft_strcmp("pwd", cmd) == 0)
		pwd(fdout);
	else if (ft_strcmp("cd", cmd) == 0)
		cd(args, gen, fdout);
	else if (ft_strcmp("echo", cmd) == 0)
		echo(args, fdout);
	else if (ft_strcmp("env", cmd) == 0)
		env(args, gen->envp, fdout);
	else if (ft_strcmp("exit", cmd) == 0)
		exitbin(args, fdout, gen);
	else if (ft_strcmp("unset", cmd) == 0)
		unset(args, gen);
	else if (ft_strcmp("clear", cmd) == 0)
		clear(fdout);
	else if (ft_strcmp("export", cmd) == 0)
		export(args, gen->envp, fdout, gen);
	else
		return (FALSE);
	return (TRUE);
}

int	executor(t_gen *gen)
{
	int		pid;
	int		i;

	i = -1;
	while (++i < gen->cmd_count)
	{
		if (!is_builtin(gen->command[i].cmd, gen->command[i].args,
				gen, gen->command[i].descriptor.out))
		{
			pid = fork();
			if (pid == 0)
				child_process(gen, i);
			else
				executor_helper2();
		}
		executor_helper(gen, i);
	}
	free_after_cmd(gen);
	return (1);
}
