/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 21:02:29 by alyasar           #+#    #+#             */
/*   Updated: 2022/07/03 12:16:05 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_error(char *str, int exit_status)
{
	write(STDERR_FILENO, "Error: ", 8);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	g_exit_status = exit_status;
}

void	exitbin(char **args, int fdout, t_gen *gen)
{
	int	i;

	write(fdout, "exit\n", 5);
	if (get_string_arr_len(args) > 2)
	{
		write_error("exit: too many arguments.", 1);
		return ;
	}
	else if (get_string_arr_len(args) == 1)
		free_all_exit(gen);
	else
	{
		g_exit_status = ft_atoi(args[1]);
		i = -1;
		while (++i < (int)ft_strlen(args[1]))
		{
			if (args[1][i] < '0' || args[1][i] > '9')
			{
				write_error("exit: numeric argument required.", 2);
				break ;
			}
		}
		free_all_exit(gen);
	}
}
