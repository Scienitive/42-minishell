/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 12:11:49 by alyasar           #+#    #+#             */
/*   Updated: 2022/07/03 12:12:13 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	if (s1[i] != s2[i])
		return (-1);
	return (0);
}

int	get_string_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	sort_2d_str_array(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (++i < get_string_arr_len(arr))
	{
		if (i < 1)
			continue ;
		j = 0;
		while (arr[i][j] != '\0' && arr[i - 1][j] != '\0')
		{
			if (arr[i][j] < arr[i - 1][j])
			{
				tmp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = tmp;
				i -= 2;
				break ;
			}
			else if (arr[i][j] > arr[i - 1][j])
				break ;
			j++;
		}
	}
}

int	ft_strcont(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	init_int_array(int *arr, int len, int val)
{
	int	i;

	i = 0;
	while (i < len)
	{
		arr[i] = val;
		i++;
	}
}
