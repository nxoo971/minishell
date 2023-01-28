/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_octal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:38:51 by nxoo              #+#    #+#             */
/*   Updated: 2022/12/31 13:09:39 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	exec_octal(va_list *param, struct s_spec_info *s)
{
	uintptr_t	n;

	n = va_arg(*param, unsigned int);
	s->current_size = len_unsigned(n, 8);
	s->is_null = n == 0;
	return (print_algo_flag(s, n, 8, faux));
}
