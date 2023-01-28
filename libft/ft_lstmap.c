/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:37:47 by ooxn              #+#    #+#             */
/*   Updated: 2022/12/31 13:11:54 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*begin;

	if (!lst)
		return (lst);
	list = ft_lstnew((*f)(lst->content));
	if (!list)
		return (list);
	begin = list;
	lst = lst->next;
	while (lst)
	{
		list->next = ft_lstnew((*f)(lst->content));
		if (!list->next)
		{
			ft_lstclear(&begin, del);
			return (list);
		}
		lst = lst->next;
		list = list->next;
	}
	return (begin);
}
