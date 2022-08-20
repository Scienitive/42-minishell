/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:22:57 by alyasar           #+#    #+#             */
/*   Updated: 2022/06/08 15:23:01 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n'
		|| c == '\v' || c == '\f')
		return (1);
	else
		return (0);
}

static void	sign_maker(const char *str, int *sign, size_t *i)
{
	if (str[*i] == '-')
	{
		*sign = -1;
		*i += 1;
	}
	else if (str[*i] == '+')
	{
		*sign = 1;
		*i += 1;
	}
	else if (str[*i] >= '0' && str[*i] <= '9')
		*sign = 1;
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		ans;

	ans = 0;
	sign = 0;
	i = 0;
	while (is_whitespace(str[i]))
		i++;
	while (str[i] != '\0')
	{
		if (sign == 0)
			sign_maker(str, &sign, &i);
		if (str[i] < '0' || str[i] > '9')
			break ;
		ans *= 10;
		ans += (str[i] - '0') * sign;
		i++;
	}
	return (ans);
}
