/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 00:40:19 by nxoo              #+#    #+#             */
/*   Updated: 2022/12/31 13:09:36 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	exec_double(va_list *param, struct s_spec_info *s)
{
	double	n;
	int		count;
	int		written;

	n = va_arg(*param, double);
	written = print_n_base((int)n, 10, faux);
	n -= (int)n;
	count = 6;
	if (s->precision >= 0)
		count = s->precision;
	if (s->width_is_specified && s->width >= 0)
		count = s->width;
	if (s->precision >= 0 || n == 0)
		written += ft_putchar_fd('.', 2);
	if (s->precision_is_specified && s->precision == -1)
		count = 0;
	while (n - (int)n < 1 && count > 0)
	{
		n *= 10;
		written += ft_putchar_fd((int)n + '0', 2);
		n -= (int)n;
		count--;
	}
	return (written);
}
