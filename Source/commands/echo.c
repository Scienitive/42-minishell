/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:51:20 by alyasar           #+#    #+#             */
/*   Updated: 2022/07/02 21:38:40 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **args, int fdout)
{
	t_bool	n_option;
	int		i;

	n_option = FALSE;
	if (get_string_arr_len(args) == 1)
	{
		write(fdout, "\n", 1);
		return ;
	}
	if (ft_strcmp("-n", args[1]) == 0)
		n_option = TRUE;
	i = n_option;
	while (++i < get_string_arr_len(args))
	{
		write(fdout, args[i], ft_strlen(args[i]));
		if (i + 1 < get_string_arr_len(args))
			write(fdout, " ", 1);
	}
	if (!n_option)
		write(fdout, "\n", 1);
	g_exit_status = 0;
}
