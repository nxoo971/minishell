/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:37:24 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/03 17:38:07 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strsub(const char *str, unsigned int start, size_t end)
{
	char		*res;
	int			i;

	res = malloc((end - start) + 1);
	if (!res)
		return (0);
	res[end - start] = 0;
	i = 0;
	while (str[start] != '\0' && start < end)
		res[i++] = str[start++];
	return (res);
}
