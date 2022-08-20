/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:38:29 by alyasar           #+#    #+#             */
/*   Updated: 2022/01/06 14:38:33 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	int	i;

	if (dest < src)
	{
		i = 0;
		while (i < (int)size)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	else
	{
		i = (int)size - 1;
		while (i >= 0)
		{	
			((char *)dest)[i] = ((char *)src)[i];
			i--;
		}
	}
	return (dest);
}
