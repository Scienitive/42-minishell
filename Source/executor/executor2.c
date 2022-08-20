/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:54:01 by alyasar           #+#    #+#             */
/*   Updated: 2022/07/03 17:50:42 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	executor_helper(t_gen *gen, int i)
{
	if (gen->command[i].descriptor.out != STDOUT_FILENO)
		close(gen->command[i].descriptor.out);
	if (gen->command[i].descriptor.in != STDIN_FILENO)
		close(gen->command[i].descriptor.in);
}

void	executor_helper2(void)
{
	signal(SIGINT, sigint2);
	wait(&g_exit_status);
	signal(SIGINT, sigint);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else
		g_exit_status = 130;
}

char	*fill_path_helper(char *path_line, int rot, int path_len)
{
	char	*path;
	int		i;
	int		j;
	int		path_num;

	path = malloc(sizeof(char) * (path_len + 1));
	i = 4;
	j = 0;
	path_num = 0;
	while (++i < (int)ft_strlen(path_line))
	{
		if (rot == path_num && path_line[i] != ':')
			path[j++] = path_line[i];
		else if (path_line[i] == ':')
			path_num++;
		if (path_num > rot)
			break ;
	}
	path[j] = '\0';
	return (path);
}

char	*fill_path(char *path_line, int rot)
{
	int		i;
	int		path_num;
	int		path_len;

	path_num = 0;
	path_len = 0;
	i = 4;
	while (++i < (int)ft_strlen(path_line))
	{
		if (rot == path_num && path_line[i] != ':')
			path_len++;
		else if (path_line[i] == ':')
			path_num++;
		if (path_num > rot)
			break ;
	}
	return (fill_path_helper(path_line, rot, path_len));
}
