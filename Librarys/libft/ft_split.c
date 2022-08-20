/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:44:17 by alyasar           #+#    #+#             */
/*   Updated: 2022/01/06 15:31:41 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && j == 0)
		{
			j = 1;
			k++;
		}
		else if (str[i] == c)
		{
			j = 0;
		}
		i++;
	}
	return (k);
}

static char	*add_to_array(const char *str, int st, int fn)
{
	char	*s;
	int		i;

	i = 0;
	s = malloc((fn - st + 1) * sizeof(char));
	while (st < fn)
		s[i++] = str[st++];
	s[i] = '\0';
	return (s);
}

char	**ft_split(char const *str, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**array;

	array = malloc((count_words(str, c) + 1) * sizeof(char *));
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(str))
	{
		if (str[i] != c && index < 0)
			index = i;
		else if ((str[i] == c || i == ft_strlen(str)) && index >= 0)
		{
			array[j++] = add_to_array(str, index, i);
			index = -1;
		}
		i++;
	}
	array[j] = 0;
	return (array);
}
