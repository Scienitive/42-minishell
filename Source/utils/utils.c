/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:46:58 by alyasar           #+#    #+#             */
/*   Updated: 2022/08/18 17:01:26 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoinf(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

int	ft_strncmpf(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (i < (int)n)
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}

char	*get_env(char *env, t_gen *gen)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < get_string_arr_len(gen->envp))
	{
		if (ft_strncmpf(gen->envp[i], env, ft_strlen(env)) == 0
			&& gen->envp[i][ft_strlen(env)] == '=')
		{
			str = malloc(sizeof(char)
					* (ft_strlen(gen->envp[i]) - ft_strlen(env)));
			j = ft_strlen(env) + 1;
			k = 0;
			while (gen->envp[i][j] != '\0')
				str[k++] = gen->envp[i][j++];
			str[k] = '\0';
			return (str);
		}
	}
	return (NULL);
}

char	**copy_str_array(char **arr)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (get_string_arr_len(arr) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < get_string_arr_len(arr))
		new[i] = ft_strdup(arr[i]);
	new[i] = 0;
	return (new);
}

int	print_error(char *str, t_gen *gen, int exit_status, int free_level)
{
	write(STDERR_FILENO, "Error: ", 8);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	g_exit_status = exit_status;
	free_on_error(gen, free_level);
	return (0);
}
