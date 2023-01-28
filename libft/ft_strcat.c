/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 04:36:08 by jewancti          #+#    #+#             */
/*   Updated: 2022/12/31 13:11:54 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	char	*start;

	start = dst;
	while (*start)
		start++;
	while (*src)
		*start++ = *src++;
	*start = 0;
	return (dst);
}
