/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:48:57 by ooxn              #+#    #+#             */
/*   Updated: 2023/01/16 00:54:03 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char		*temp;
	char		*res;
	size_t		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i < start)
		i++;
	if (!str[i] || i != start)
		return (ft_strdup(""));
	temp = malloc(len + 1);
	if (!temp)
		return (temp);
	i = 0;
	while (str[start + i] != '\0' && i < len)
	{
		temp[i] = str[start + i];
		i++;
	}
	temp[i] = '\0';
	res = ft_strdup(temp);
	ft_memdel((void **)& temp);
	return (res);
}
