/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:22:27 by alyasar           #+#    #+#             */
/*   Updated: 2022/07/03 19:02:39 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_old_pwd(t_gen *gen, int fdout)
{
	char	*env;

	env = get_env("OLDPWD", gen);
	if (!env)
	{
		print_error("cd: OLDPWD not set.", gen, 1, 0);
		return ;
	}
	if (chdir(env) == -1)
	{
		print_error("cd: not a directory.", gen, 1, 0);
		free(env);
		return ;
	}
	write(fdout, env, ft_strlen(env));
	write(fdout, "\n", 1);
	free(env);
	g_exit_status = 0;
	return ;
}

char	*cd_change_arg(char *arg, t_gen *gen)
{
	char	*new_arg;
	int		i;
	int		j;

	new_arg = malloc(sizeof(char)
			* (ft_strlen(arg) + ft_strlen(gen->home_path)));
	i = -1;
	while (++i < (int)ft_strlen(gen->home_path))
		new_arg[i] = gen->home_path[i];
	j = 1;
	while (arg[j] != '\0')
	{
		new_arg[i++] = arg[j];
		j++;
	}
	new_arg[i] = '\0';
	free(arg);
	return (new_arg);
}

void	cd_home(t_gen *gen)
{
	char	*env;

	env = get_env("HOME", gen);
	if (!env)
	{
		print_error("cd: HOME not set.", gen, 1, 0);
		return ;
	}
	if (chdir(env) == -1)
	{
		print_error("cd: not a directory.", gen, 1, 0);
		free(env);
		return ;
	}
	free(env);
	g_exit_status = 0;
	return ;
}

void	cd(char **args, t_gen *gen, int fdout)
{
	if (get_string_arr_len(args) == 1)
	{
		cd_home(gen);
		return ;
	}
	if (get_string_arr_len(args) > 2)
	{
		print_error("cd: too many arguments.", gen, 1, 0);
		return ;
	}
	if (args[1][0] == '~' && (args[1][1] == '\0' || args[1][1] == '/')
		&& gen->home_path != NULL)
		args[1] = cd_change_arg(args[1], gen);
	if (args[1][0] == '-' && args[1][1] == '\0')
		cd_old_pwd(gen, fdout);
	else if (chdir(args[1]) == -1)
	{
		print_error("cd: not a directory.", gen, 1, 0);
		return ;
	}
	g_exit_status = 0;
}
