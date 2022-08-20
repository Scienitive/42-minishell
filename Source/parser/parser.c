/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:25:49 by alyasar           #+#    #+#             */
/*   Updated: 2022/08/18 16:56:58 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	argument(t_gen *gen, int *i, int *j, int *cmd_i)
{
	gen->command[*cmd_i].args[(*j)++] = ft_strdup(gen->cmd_line[*i]);
	gen->command[*cmd_i].args[*j] = 0;
	return (1);
}

void	create_pipe(t_gen *gen, int cmd_i)
{
	int	fd[2];

	if (cmd_i == gen->cmd_count - 1)
	{
		gen->command[cmd_i].descriptor.in = gen->pipe_holder;
		gen->command[cmd_i].descriptor.out = STDOUT_FILENO;
		gen->command[cmd_i].descriptor.err = STDERR_FILENO;
	}
	else
	{
		pipe(fd);
		gen->command[cmd_i].descriptor.in = gen->pipe_holder;
		gen->command[cmd_i].descriptor.out = fd[1];
		gen->command[cmd_i].descriptor.err = STDERR_FILENO;
		gen->pipe_holder = fd[0];
	}
}

int	command(t_gen *gen, int *i, int *j, int *cmd_i)
{
	*j = 0;
	gen->command[++(*cmd_i)].cmd = ft_strdup(gen->cmd_line[*i]);
	gen->command[*cmd_i + 1].cmd = 0;
	gen->command[*cmd_i].args = malloc(sizeof(char *)
			* (gen->arg_counts[*cmd_i] + 1));
	if (!gen->command[*cmd_i].args)
		return (print_error("allocation error.", gen, 1, 3));
	gen->command[*cmd_i].args[(*j)++] = ft_strdup(gen->cmd_line[*i]);
	gen->command[*cmd_i].args[*j] = 0;
	create_pipe(gen, *cmd_i);
	return (1);
}

int	token_operations(t_gen *gen, int *i, int *j, int *cmd_i)
{
	if (gen->tokens[*i] == COMMAND)
		return (command(gen, i, j, cmd_i));
	else if (gen->tokens[*i] == ARGUMENT)
		return (argument(gen, i, j, cmd_i));
	else if (gen->tokens[*i] == GREATER)
		return (greater(gen, i, cmd_i));
	else if (gen->tokens[*i] == DGREATER)
		return (dgreater(gen, i, cmd_i));
	else if (gen->tokens[*i] == LESSER)
		return (lesser(gen, i, cmd_i));
	else if (gen->tokens[*i] == DLESSER)
		return (dlesser(gen, i, cmd_i));
	return (1);
}

int	parser(t_gen *gen)
{
	int		i;
	int		j;
	int		cmd_i;

	gen->pipe_holder = STDIN_FILENO;
	gen->command = malloc(sizeof(t_command) * (gen->cmd_count + 1));
	if (!gen->command)
		return (print_error("allocation error.", gen, 1, 2));
	i = -1;
	cmd_i = -1;
	while (++i < gen->token_count)
	{
		if (!token_operations(gen, &i, &j, &cmd_i))
			return (0);
	}
	return (1);
}
