/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:14:09 by ooxn              #+#    #+#             */
/*   Updated: 2022/12/31 13:11:54 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static size_t	ft_wordcount(const char *s, char c)
{
	int		i;
	size_t	len;

	len = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			len++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (len);
}

void	fill_words(char **tab, const char *s, char c, size_t len)
{
	int		i;
	int		j;
	int		k;
	size_t	index;

	i = 0;
	index = 0;
	while (index < len)
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[j] && s[j] != c)
			j++;
		tab[index] = malloc((j - i) + 1);
		if (!tab[index])
			return ;
		k = 0;
		while (i < j)
			tab[index][k++] = s[i++];
		tab[index][k] = 0;
		index++;
	}
	tab[index] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_wordcount(s, c);
	res = malloc(sizeof(char *) * (len + 1));
	if (res)
		fill_words(res, s, c, len);
	return (res);
}
