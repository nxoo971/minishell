/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 20:30:25 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/24 11:42:31 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	size_t	i;
	char	*s;

	len = ft_strlen(s1);
	if (len < n)
		s = malloc(len + 1);
	else
		s = malloc(n + 1);
	if (s)
	{
		i = 0;
		while (i < n && s1[i])
		{
			s[i] = s1[i];
			i++;
		}
		s[i] = 0;
	}
	return (s);
}
