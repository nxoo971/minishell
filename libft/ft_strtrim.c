/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:42:51 by ooxn              #+#    #+#             */
/*   Updated: 2023/01/03 17:52:10 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	is_set(const char *set, char c)
{
	while (*set && *set != c)
		set++;
	return (*set != '\0');
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*s;

	if (!s1 || !set)
		return (NULL);
	s = (char *)s1;
	while (*s && is_set(set, *s))
		s++;
	if (!*s)
		return (ft_strdup(s));
	start = s;
	while (*s)
		s++;
	while (is_set(set, *--s))
		;
	return (ft_strsub(start, 0, ++s - start));
}
