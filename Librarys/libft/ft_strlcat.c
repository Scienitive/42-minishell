/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:39:33 by alyasar           #+#    #+#             */
/*   Updated: 2022/01/06 14:39:34 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	destlen;

	destlen = ft_strlen(dest);
	i = 0;
	if (destlen < size - 1 && size > 0)
	{
		while (src[i] != '\0' && destlen + i < size - 1)
		{
			dest[destlen + i] = src[i];
			i++;
		}
		dest[destlen + i] = '\0';
	}
	if (destlen > size)
		destlen = size;
	return (destlen + ft_strlen(src));
}
