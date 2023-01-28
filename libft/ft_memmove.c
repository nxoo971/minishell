/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:31:46 by ooxn              #+#    #+#             */
/*   Updated: 2023/01/16 00:54:03 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*tmp;

	if (!dst && !src)
		return (NULL);
	tmp = malloc(len);
	if (tmp)
	{
		ft_memcpy(tmp, src, len);
		ft_memcpy(dst, tmp, len);
		ft_memdel((void **)& tmp);
	}
	return (dst);
}
