/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:10:32 by alyasar           #+#    #+#             */
/*   Updated: 2022/08/09 12:58:33 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint2(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
}

void	restore_sigint(t_gen *gen)
{
	signal(SIGINT, gen->sigint_handler);
	signal(SIGQUIT, gen->sigquit_handler);
}

void	sigint_dlesser(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	g_exit_status = 130;
	close(STDIN_FILENO);
}

void	sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	g_exit_status = 130;
	rl_replace_line("", STDIN_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals(t_gen *gen)
{
	gen->sigint_handler = signal(SIGINT, sigint);
	gen->sigquit_handler = signal(SIGQUIT, SIG_IGN);
}
