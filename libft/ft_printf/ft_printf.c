/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 01:05:09 by nxoo              #+#    #+#             */
/*   Updated: 2023/01/03 17:05:30 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

enum
{
	STRING,
	SPECIFICATION,
	COLOR
}
e_state;

static int	print_substring(const char *start, const char *end)
{
	return (ft_putnstr_fd(start, end - start, 2));
}

static int	is_specifier(char c)
{
	static const char *const	names[256] = {
	['c'] = "char",
	['s'] = "char *",
	['p'] = "pointer",
	['d'] = "int",
	['i'] = "int",
	['u'] = "unsigned",
	['x'] = "unsigned hexa",
	['X'] = "unsigned hexa",
	['f'] = "float / double",
	['o'] = "octal",
	['b'] = "binary",
	['%'] = "percent",
	};

	return (names[(unsigned)c] != NULL);
}

static t_bool	case_string_specification(const char **start, const char **end, \
											int *len, va_list *params)
{
	if (e_state == STRING)
	{
		if (**end == '%' || **end == '{')
		{
			*len += print_substring(*start, *end);
			if (**end == '%')
				e_state = SPECIFICATION;
			else
				e_state = COLOR;
			*start = *end;
		}
	}
	else if (e_state == SPECIFICATION)
	{
		if (is_specifier(**end))
		{
			*len += explain_specification(*start, *end + 1, params);
			e_state = STRING;
			*start = *end + 1;
		}
	}
	return (e_state == STRING || e_state == SPECIFICATION);
}

static void	main_printf(const char *start, const char *end, \
							int *len, va_list *params)
{
	while (*end != '\0')
	{
		if (!case_string_specification(&start, &end, len, params))
		{
			if (*end == '}')
			{
				if (ft_strnrchr(start, '{', end - start) != start)
				{
					print_substring(start, \
						ft_strnrchr(start, '{', end - start));
					start = ft_strnrchr(start, '{', end - start);
				}
				if (end[-1] == '{')
					print_substring(start - 1, end + 1);
				if (explain_color(start, end + 1))
					e_state = STRING;
				else
					*len += print_substring(start, end + 1);
				start = end + 1;
			}
		}
		end++;
	}
	*len += print_substring(start, end);
}

int	ft_printf(const char *format, ...)
{
	va_list		params;
	int			len;
	const char	*p;
	const char	*start;

	p = format;
	start = format;
	e_state = STRING;
	len = 0;
	va_start(params, format);
	main_printf(start, p, &len, &params);
	va_end(params);
	return (len);
}
