/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 21:10:57 by alyasar           #+#    #+#             */
/*   Updated: 2022/07/03 11:34:32 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_error(char *str, int exit_status)
{
	write(STDERR_FILENO, "Error: ", 8);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	g_exit_status = exit_status;
}

void	env(char **args, char **envp, int fdout)
{
	int	i;

	if (get_string_arr_len(args) > 1)
	{
		write_error("env: too many arguments.", 1);
		return ;
	}
	i = -1;
	while (++i < get_string_arr_len(envp))
	{
		if (ft_strcont(envp[i], '='))
		{
			write(fdout, envp[i], ft_strlen(envp[i]));
			write(fdout, "\n", 1);
		}
	}
	g_exit_status = 0;
}
