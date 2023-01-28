/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:19:48 by ooxn              #+#    #+#             */
/*   Updated: 2023/01/16 00:54:03 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && lst->content)
	{
		del(lst->content);
		ft_memdel((void **)& lst);
		lst = NULL;
	}
}
