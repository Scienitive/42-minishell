/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 18:51:50 by alyasar           #+#    #+#             */
/*   Updated: 2022/08/08 13:05:00 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_str_array(char **arr)
{
	int	i;

	i = -1;
	while (++i < get_string_arr_len(arr))
		free(arr[i]);
	free(arr);
}

void	free_after_cmd(t_gen *gen)
{
	int	i;

	i = -1;
	while (++i < gen->cmd_count)
	{
		free(gen->command[i].cmd);
		free_str_array(gen->command[i].args);
	}
	free(gen->command);
	free(gen->arg_counts);
	free(gen->tokens);
	free_str_array(gen->cmd_line);
}

void	free_on_exit(t_gen *gen)
{
	free_str_array(gen->envp);
	free(gen->home_path);
}

void	free_all_exit(t_gen *gen)
{
	free_after_cmd(gen);
	free_on_exit(gen);
	exit(g_exit_status);
}

int	free_on_error(t_gen *gen, int level)
{
	int	i;

	if (level >= 1)
	{
		free(gen->tokens);
		free_str_array(gen->cmd_line);
	}
	if (level >= 2)
		free(gen->arg_counts);
	if (level >= 3)
	{
		i = -1;
		while (gen->command[++i].cmd != NULL)
		{
			free(gen->command[i].cmd);
			if (gen->command[i].args)
				free_str_array(gen->command[i].args);
		}
		free(gen->command);
	}
	return (0);
}
