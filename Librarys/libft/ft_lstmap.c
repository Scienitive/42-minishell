/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:47:58 by alyasar           #+#    #+#             */
/*   Updated: 2022/01/07 10:45:55 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_element;
	t_list	*ptr_first;

	if (lst == NULL || f == NULL)
		return (NULL);
	ptr_first = 0;
	while (lst)
	{
		new_element = ft_lstnew(f(lst->content));
		if (new_element == NULL)
		{
			ft_lstclear(&ptr_first, del);
			return (NULL);
		}
		ft_lstadd_back(&ptr_first, new_element);
		lst = lst->next;
	}
	return (ptr_first);
}
