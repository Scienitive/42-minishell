/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:36:17 by alyasar           #+#    #+#             */
/*   Updated: 2022/06/30 21:13:46 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(int fdout)
{
	char	buf[256];

	getcwd(buf, 256);
	write(fdout, &buf, ft_strlen(buf));
	write(fdout, "\n", 1);
	g_exit_status = 0;
}
