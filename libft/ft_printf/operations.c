/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:21:00 by nxoo              #+#    #+#             */
/*   Updated: 2022/12/31 13:09:50 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

#define SIZE	2 /* upper and lower base */

int	print_n_base(uintptr_t n, int base, t_bool lower)
{
	static int					len;
	static const char *const	bases[SIZE] = {BASE, LOWERBASE};

	len = 0;
	if (n >= (unsigned)base)
		print_n_base(n / base, base, lower);
	len += ft_putchar_fd(bases[lower][n % base], 2);
	return (len);
}
