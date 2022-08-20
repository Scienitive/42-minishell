/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:17:08 by alyasar           #+#    #+#             */
/*   Updated: 2022/08/08 13:04:55 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d(t_gen *gen)
{
	write(STDOUT_FILENO, "exit\n", 5);
	free_on_exit(gen);
	exit(EXIT_SUCCESS);
}

char	*get_prompt(void)
{
	char		*prompt;
	char		buf[256];

	getcwd(buf, 256);
	prompt = ft_strdup("\e[1;32m#minishell#\e[0;37m:\e[1;34m");
	prompt = ft_strjoinf(prompt, buf);
	prompt = ft_strjoinf(prompt, "\e[0m$ ");
	return (prompt);
}

int	start_init(t_gen *gen, int argc, char **argv, char **envp)
{
	if (argc > 1 && argv)
		return (print_error("too many arguments.", gen, 1, 0));
	gen->envp = copy_str_array(envp);
	gen->home_path = get_env("HOME", gen);
	set_signals(gen);
	clear(STDOUT_FILENO);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_gen	gen;
	char	*line;
	char	*prompt;

	if (!start_init(&gen, argc, argv, envp))
		return (1);
	while (1)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (line == NULL)
			ctrl_d(&gen);
		if (line[0] != '\0')
		{
			add_history(line);
			if (lexer(&gen, line))
			{
				if (parser(&gen))
					executor(&gen);
			}
		}
	}
	return (0);
}
