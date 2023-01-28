/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 02:18:32 by ooxn              #+#    #+#             */
/*   Updated: 2022/12/31 13:11:54 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

ssize_t	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	static ssize_t	written;

	written = 0;
	nb = n;
	if (n < 0)
	{
		nb = n * -1;
		written += ft_putchar_fd('-', fd);
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	written += ft_putchar_fd(nb % 10 + '0', fd);
	return (written);
}
