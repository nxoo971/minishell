/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_displaydouble.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:49:46 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/24 11:43:08 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdio.h>

void	ft_displaydouble(char **str)
{
	int	i;

	i = -1;
	if (!str || !*str)
		return ;
	while (str[++i])
		fprintf(stderr, "[%s] ", str[i]);
	ft_putchar('\n');
}
