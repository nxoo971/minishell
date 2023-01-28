/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:50:48 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/26 18:02:49 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_option(const char *opt)
{
	int	i;

	i = 0;
	if (!opt || !opt[0])
		return (0);
	if (opt[i++] != '-')
		return (0);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	print(const char **arg, int i)
{
	int	boolean;

	boolean = (i > 0);
	while (arg[i])
	{
		if (arg[i + 1])
		{
			ft_putstr(arg[i]);
			ft_putstr(" ");
		}
		else
			ft_putstr(arg[i]);
		i++;
	}
	if (!boolean)
		ft_putstr("\n");
}

void	echo(const char **arg)
{
	int	i;

	i = 0;
	while (arg[i] && is_valid_option(arg[i]))
		i++;
	print(arg, i);
}
