/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 02:33:37 by nxoo              #+#    #+#             */
/*   Updated: 2022/12/31 14:42:48 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static \
int	precision_greater_than_currentsize(\
	const struct s_spec_info *s, uintptr_t n, int base, t_bool lower)
{
	int	width;
	int	prec;
	int	written;

	width = 0;
	written = 0;
	prec = (s->precision - s->current_size) + (int)s->is_negative;
	if (s->width_is_specified && s->width >= s->precision)
		width = (s->width - s->precision) - s->is_negative - \
			(s->space && !s->is_negative) - (s->plus && !s->is_negative);
	if (!s->is_left_aligned)
		written += print_width(width, ' ');
	written += print_sign(s) + print_prefix(s);
	if (s->is_left_aligned && !prec)
		return (written + print_n_base(n, base, lower) + \
			print_width(width, ' '));
	written += print_width(prec, '0');
	if (s->is_left_aligned && prec)
		return (written + print_n_base(n, base, lower) + \
			print_width(width, ' '));
	return (written + print_n_base(n, base, lower));
}

/* [0] = base | [1] = width | [2] = prec | [3] = written */

static \
int	width_greater_than_currentsize(\
const struct s_spec_info *s, uintptr_t n, int bs[4], t_bool lower)
{
	if (s->width_is_specified && s->width > s->current_size - (int)s->is_null)
	{
		bs[1] = (s->width - s->current_size) - (s->space && !s->plus);
		if (s->precision <= 0 && s->is_null)
			bs[1] = s->width - (s->space && !s->plus);
		if (s->space && s->is_negative)
			bs[1] += 1;
		if (s->current_type == 'd' || s->current_type == 'i')
			bs[1] -= (s->plus && !s->space && !s->is_negative);
		if (!s->is_left_aligned)
			bs[3] += print_width(bs[1], ' ') + print_sign(s) + print_prefix(s);
		else
			bs[3] += print_sign(s) + print_prefix(s);
		if (s->is_left_aligned)
		{
			if (!s->is_null || (s->is_null && s->precision > 0))
				bs[3] += print_n_base(n, bs[0], lower);
			return (bs[3] + print_width(bs[1], ' '));
		}
	}
	else
		bs[3] += print_sign(s) + print_prefix(s);
	if (s->precision <= 0 && s->is_null)
		return (bs[3]);
	return (bs[3] + print_n_base(n, bs[0], lower));
}

int	print_algo_flag(const struct s_spec_info *s, \
	uintptr_t n, int base, t_bool lower)
{
	int	width;
	int	prec;
	int	written;

	width = 0;
	prec = 0;
	written = 0;
	if (!s->precision_is_specified)
		return (precision_is_not_specified(s, n, base, lower));
	if (s->precision_is_specified)
	{
		if (s->precision > s->current_size - (int)s->is_negative)
			return (precision_greater_than_currentsize(s, n, base, lower));
	}
	return (width_greater_than_currentsize(\
		s, n, (int [4]){base, width, prec, written}, lower));
}
