/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:56:29 by alyasar           #+#    #+#             */
/*   Updated: 2022/01/06 15:11:47 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*ptr;

	ptr = malloc(size * count);
	i = 0;
	while (i < size * count)
	{
		((unsigned char *)(ptr))[i] = (unsigned char)('\0');
		i++;
	}
	return (ptr);
}
