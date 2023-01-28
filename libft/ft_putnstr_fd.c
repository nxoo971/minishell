/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 23:34:58 by nxoo              #+#    #+#             */
/*   Updated: 2022/12/31 13:11:54 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

ssize_t	ft_putnstr_fd(const char *s, size_t len, int fd)
{
	size_t	i;

	if (s)
	{
		i = 0;
		while (s[i] && i < len)
			i++;
		return (write(fd, s, i));
	}
	return (0);
}
