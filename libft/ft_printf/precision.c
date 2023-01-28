/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 00:15:23 by jewancti          #+#    #+#             */
/*   Updated: 2022/12/31 13:09:53 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/* 0 = base | 1 = width | 2 = c*/
static \
int	_prec(const struct s_spec_info *s, \
				uintptr_t n, int base[3], t_bool lower)
{
	if (!s->with_leading_zeroes && s->is_left_aligned)
		return (print_sign(s) + print_prefix(s) + \
			print_n_base(n, base[0], lower) + print_width(base[1], base[2]));
	if (!s->with_leading_zeroes)
		return (print_width(base[1], base[2]) + \
			print_prefix(s) + print_sign(s) + print_n_base(n, base[0], lower));
	if (s->is_left_aligned)
		return (print_sign(s) + print_prefix(s) + \
			print_n_base(n, base[0], lower) + print_width(base[1], base[2]));
	return (print_sign(s) + print_prefix(s) + \
		print_width(base[1], base[2]) + print_n_base(n, base[0], lower));
}

int	precision_is_not_specified(const struct s_spec_info *s, \
									uintptr_t n, int base, t_bool lower)
{
	int	c;
	int	width;

	c = '0';
	width = 0;
	if (s->width_is_specified && s->width > 0)
	{
		if (s->current_size <= s->width)
		{
			width = (s->width - s->current_size) + s->all;
			width -= (s->space && !s->plus);
			if (s->space && s->is_negative && !s->is_null)
				width += 1;
			if (s->current_type == 'd' || s->current_type == 'i')
			{
				width -= (s->plus && !s->space && !s->is_negative);
				if (s->all)
					width -= 2;
			}
		}
		if (!s->with_leading_zeroes || \
			(s->with_leading_zeroes && s->is_left_aligned))
			c = ' ';
	}
	return (_prec(s, n, (int [3]){base, width, c}, lower));
}
