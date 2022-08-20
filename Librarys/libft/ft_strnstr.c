/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:40:43 by alyasar           #+#    #+#             */
/*   Updated: 2022/02/06 14:40:20 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lil, size_t len)
{
	size_t	i;
	size_t	j;

	if (lil[0] == '\0')
		return ((char *) big);
	j = ft_strlen(lil);
	while (*big != '\0' && len >= j)
	{
		i = 0;
		while (lil[i] == big[i])
		{
			i++;
			if (lil[i] == '\0')
				return ((char *) big);
		}
		big++;
		len--;
	}
	return (NULL);
}
