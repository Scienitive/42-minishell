/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:47:39 by alyasar           #+#    #+#             */
/*   Updated: 2022/01/07 11:24:01 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*ptr;

	ptr = lst;
	size = 0;
	if (ptr)
	{
		size++;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
			size++;
		}
	}
	return (size);
}
