/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 12:11:13 by alyasar           #+#    #+#             */
/*   Updated: 2022/07/03 18:50:44 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_and_ret(char *str)
{
	free(str);
	return (0);
}

void	add_to_env(char *line, t_gen *gen)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * (get_string_arr_len(gen->envp) + 2));
	i = -1;
	while (++i < get_string_arr_len(gen->envp))
		new_envp[i] = gen->envp[i];
	new_envp[i++] = line;
	new_envp[i] = 0;
	free(gen->envp);
	gen->envp = new_envp;
}

int	get_key_index(char *env, t_gen *gen)
{
	int	i;

	i = -1;
	while (++i < get_string_arr_len(gen->envp))
	{
		if (ft_strncmpf(gen->envp[i], env, ft_strlen(env)) == 0)
			return (i);
	}
	return (-1);
}
