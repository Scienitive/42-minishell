/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 21:10:15 by alyasar           #+#    #+#             */
/*   Updated: 2022/07/02 21:33:16 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_helper(char *var, t_gen *gen)
{
	char	**new_envp;
	int		i;
	int		j;

	new_envp = malloc(sizeof(char *) * (get_string_arr_len(gen->envp) + 1));
	i = -1;
	j = 0;
	while (++i < get_string_arr_len(gen->envp))
	{
		if (ft_strncmpf(var, gen->envp[i], ft_strlen(var)) == 0)
			continue ;
		new_envp[j++] = ft_strdup(gen->envp[i]);
	}
	new_envp[j] = 0;
	free_str_array(gen->envp);
	gen->envp = new_envp;
}

t_bool	is_it_env(char *var, t_gen *gen)
{
	int	i;

	i = -1;
	while (++i < get_string_arr_len(gen->envp))
	{
		if (ft_strncmpf(var, gen->envp[i], ft_strlen(var)))
			return (TRUE);
	}
	return (FALSE);
}

void	unset(char **args, t_gen *gen)
{
	int	i;

	i = 0;
	while (++i < get_string_arr_len(args))
	{
		if (is_it_env(args[i], gen))
			unset_helper(args[i], gen);
	}
	g_exit_status = 0;
}
