/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_spec_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 21:06:24 by nxoo              #+#    #+#             */
/*   Updated: 2022/12/31 13:09:44 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static \
struct s_spec_info	init_spec(void)
{
	static const struct s_spec_info	s = {
		.is_left_aligned = faux,
		.with_leading_zeroes = faux,
		.space = faux,
		.plus = faux,
		.sharp = faux,
		.width_is_specified = faux,
		.width = 0,
		.precision_is_specified = faux,
		.precision = -1,
		.half_count = 0,
		.long_count = 0,
		.is_size_t = faux,
		.current_type = -1,
		.is_negative = faux,
		.current_size = 0,
		.is_null = faux,
	};

	return (s);
}

static \
void	pre_check(struct s_spec_info *s)
{
	s->all = (s->space && s->plus && s->is_left_aligned && s->sharp);
	if (s->plus && s->current_type != 'd' && s->current_type != 'i')
		s->plus = faux;
	if (s->sharp && s->current_type != 'x' && s->current_type != 'X')
		s->sharp = faux;
}

struct s_spec_info	extract_spec_info(const char *start, const char *end)
{
	struct s_spec_info			s;
	const char					*p;

	p = start + 1;
	s = init_spec();
	while (accept_flag_char(& s, *p))
		p++;
	while (accept_width_char(& s, *p))
		p++;
	if (*p == '.')
	{
		p++;
		s.precision_is_specified = vrai;
		while (accept_precision_char(& s, *p))
			p++;
	}
	while (accept_type_char(& s, *p))
		p++;
	s.current_type = end[-1];
	pre_check(&s);
	return (s);
}
