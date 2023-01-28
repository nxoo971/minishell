/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 04:33:51 by nxoo              #+#    #+#             */
/*   Updated: 2022/12/31 13:11:54 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_swap(void *a, void *b, size_t const n)
{
	size_t			i;
	unsigned char	*cur_a;
	unsigned char	*cur_b;
	unsigned char	tmp;

	i = 0;
	while (i < n)
	{
		cur_a = a + i;
		cur_b = b + i;
		tmp = *cur_a;
		*cur_a = *cur_b;
		*cur_b = tmp;
		i++;
	}
}
