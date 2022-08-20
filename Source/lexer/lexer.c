/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:27:44 by alyasar           #+#    #+#             */
/*   Updated: 2022/08/18 17:05:15 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lex_check(t_gen *gen)
{
	int		i;

	i = -1;
	while (++i < gen->token_count)
	{
		if ((gen->tokens[i] >= PIPE && gen->tokens[i] <= DLESSER)
			&& ((i + 1 >= gen->token_count)
				|| (gen->tokens[i + 1] >= PIPE
					&& gen->tokens[i + 1] <= DLESSER)))
		{
			return (print_error("syntax error", gen, 1, 2));
		}
	}
	return (1);
}

void	set_unknowns(t_gen *gen, int *i, int *j)
{
	while (++(*i) < gen->token_count)
	{
		if (gen->tokens[*i] == UNKNOWN)
		{
			if (gen->tokens[*i - 1] == COMMAND
				|| gen->tokens[*i - 1] == ARGUMENT)
			{
				gen->tokens[*i] = ARGUMENT;
				gen->arg_counts[*j]++;
			}
			else if (gen->tokens[*i - 1] >= GREATER
				&& gen->tokens[*i - 1] <= DLESSER)
				gen->tokens[*i] = FILENAME;
			else if (gen->tokens[*i - 1] == FILENAME)
			{
				gen->tokens[*i] = ARGUMENT;
				gen->arg_counts[*j]++;
			}
		}
		else if (gen->tokens[*i] == COMMAND)
			(*j)++;
	}
}

int	lexer2(t_gen *gen)
{
	int		i;
	int		j;

	i = 0;
	while (++i < gen->token_count)
	{
		if (gen->tokens[i] == UNKNOWN && gen->tokens[i - 1] == PIPE)
		{
			gen->tokens[i] = COMMAND;
			gen->cmd_count++;
		}
	}
	gen->arg_counts = malloc(sizeof(int) * gen->cmd_count);
	if (!gen->arg_counts)
		return (print_error("allocation error.", gen, 1, 1));
	init_int_array(gen->arg_counts, gen->cmd_count, 1);
	i = 0;
	j = 0;
	set_unknowns(gen, &i, &j);
	return (lex_check(gen));
}

void	set_tokens(t_gen *gen)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (++i < gen->token_count)
	{
		if (!ft_strcmp(gen->cmd_line[i], "|") && !gen->redir_mark[j])
			gen->tokens[i] = PIPE;
		else if (!ft_strcmp(gen->cmd_line[i], ">>") && !gen->redir_mark[j])
			gen->tokens[i] = DGREATER;
		else if (!ft_strcmp(gen->cmd_line[i], "<<") && !gen->redir_mark[j])
			gen->tokens[i] = DLESSER;
		else if (!ft_strcmp(gen->cmd_line[i], ">") && !gen->redir_mark[j])
			gen->tokens[i] = GREATER;
		else if (!ft_strcmp(gen->cmd_line[i], "<") && !gen->redir_mark[j])
			gen->tokens[i] = LESSER;
		else
		{
			j--;
			gen->tokens[i] = UNKNOWN;
		}
		j++;
	}
}

int	lexer(t_gen *gen, char *line)
{
	gen->cmd_line = split_line(line, gen);
	if (!gen->cmd_line)
		return (print_error("something wrong with quotes.", gen, 1, 0));
	gen->token_count = get_string_arr_len(gen->cmd_line);
	if (!gen->token_count)
	{
		g_exit_status = 0;
		free_on_error(gen, 0);
		free_str_array(gen->cmd_line);
		return (0);
	}
	gen->tokens = malloc(sizeof(t_token) * gen->token_count);
	gen->tokens[0] = COMMAND;
	gen->cmd_count = 1;
	set_tokens(gen);
	if (gen->redir_len > 0)
		free(gen->redir_mark);
	return (lexer2(gen));
}
