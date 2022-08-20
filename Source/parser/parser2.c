/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:35:05 by alyasar           #+#    #+#             */
/*   Updated: 2022/08/08 15:22:56 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dlesser_child(t_gen *gen, int i, int fd[2])
{
	char	*line;

	close(fd[0]);
	g_exit_status = 0;
	signal(SIGINT, sigint_dlesser);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			if (g_exit_status == 130)
				free_all_exit(gen);
			else
			{
				print_error("warning: delimited by end-of-file.", gen, 0, 0);
				break ;
			}
		}
		if (ft_strcmp(line, gen->cmd_line[i + 1]) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	free_all_exit(gen);
}

int	dlesser(t_gen *gen, int	*i, int *cmd_i)
{
	int	pid;
	int	fd[2];
	int	es;

	pipe(fd);
	pid = fork();
	if (pid == 0)
		dlesser_child(gen, *i, fd);
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	wait(&es);
	signal(SIGINT, sigint);
	es = WEXITSTATUS(es);
	if (es == 130)
		return (free_on_error(gen, 3));
	gen->command[*cmd_i].descriptor.in = fd[0];
	return (1);
}

int	lesser(t_gen *gen, int *i, int *cmd_i)
{
	if (gen->command[*cmd_i].descriptor.in != STDIN_FILENO)
		close(gen->command[*cmd_i].descriptor.in);
	gen->command[*cmd_i].descriptor.in
		= open(gen->cmd_line[*i + 1], O_RDONLY);
	if (gen->command[*cmd_i].descriptor.in == -1)
		return (print_error("no such file or directory.", gen, 1, 3));
	return (1);
}

int	dgreater(t_gen *gen, int *i, int *cmd_i)
{
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (gen->command[*cmd_i].descriptor.out != STDOUT_FILENO)
		close(gen->command[*cmd_i].descriptor.out);
	gen->command[*cmd_i].descriptor.out
		= open(gen->cmd_line[*i + 1], O_WRONLY | O_CREAT | O_APPEND, mode);
	if (gen->command[*cmd_i].descriptor.out == -1)
		return (print_error("invalid file descriptor.", gen, 1, 3));
	return (1);
}

int	greater(t_gen *gen, int *i, int *cmd_i)
{
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (gen->command[*cmd_i].descriptor.out != STDOUT_FILENO)
		close(gen->command[*cmd_i].descriptor.out);
	gen->command[*cmd_i].descriptor.out
		= open(gen->cmd_line[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, mode);
	if (gen->command[*cmd_i].descriptor.out == -1)
		return (print_error("invalid file descriptor.", gen, 1, 3));
	return (1);
}
