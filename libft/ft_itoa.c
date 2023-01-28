/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:10:53 by ooxn              #+#    #+#             */
/*   Updated: 2022/12/31 13:11:54 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	length_integer(unsigned int nb)
{
	static int	len;

	len = 0;
	if (nb >= 10)
		length_integer(nb / 10);
	len++;
	return (len);
}

void	set_nb(int n, char **res, int pos)
{
	unsigned int	nb;

	nb = n;
	if (n < 0)
	{
		nb = n * -1;
		(*res)[0] = '-';
	}
	if (nb >= 10)
		set_nb(nb / 10, res, pos - 1);
	(*res)[pos] = nb % 10 + '0';
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*res;

	if (n < 0)
		len = 1 + length_integer(n * -1);
	else
		len = length_integer(n);
	res = malloc(len + 1);
	if (!res)
		return (res);
	res[len] = 0;
	set_nb(n, &res, len - 1);
	return (res);
}
