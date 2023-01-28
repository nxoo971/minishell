/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varvide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:32:19 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/26 20:46:01 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

static int	many_nb(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] && str[i] != '|')
	{
		while (str[i] && !is_in_charset(str[i], "<>|") && ft_isspace(str[i]))
			i++;
		if (str[i] != VARVIDE && !is_in_charset(str[i], "<>|"))
			count++;
		while (str[i] && !ft_isspace(str[i]) && str[i] != '|')
			i++;
	}
	return (count);
}

static char	*epurstr(char *str)
{
	int		len;
	int		j;
	char	*s;
	char	*new;

	len = ft_strlen(str);
	s = str;
	new = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	j = 0;
	while (len && ft_isspace(s[len - 1]))
		--len;
	while (len && ft_isspace(*s) && *s++)
		--len;
	while (len--)
	{
		if (!ft_isspace(*s) || (*(s + 1) && !ft_isspace(*(s + 1))))
			new[j++] = *s;
		s++;
	}
	new[j] = 0;
	return (new);
}

static void	subretransform(char *epur, char *new, int *i, int *j)
{
	if (epur[*i] && is_in_charset(epur[*i], "<>") && epur[*i + 1]
		&& epur[*i + 2] && is_in_charset(epur[*i + 2], "<>"))
	{
		new[(*j)++] = epur[(*i)++];
		new[(*j)++] = ' ';
		new[(*j)++] = SLASHBACK;
		new[(*j)++] = ' ';
	}
	else if (epur[*i] && is_in_charset(epur[*i], "<>") && !epur[*i + 1])
	{
		new[(*j)++] = epur[(*i)++];
		new[(*j)++] = ' ';
		new[(*j)++] = SLASHBACK;
	}
	else
		new[(*j)++] = epur[(*i)++];
}

static char	*retransform(char *str)
{
	char	*new;
	char	*epur;
	int		i;
	int		j;

	new = malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!new)
		return (NULL);
	epur = epurstr(str);
	if (!epur)
	{
		ft_memdel((void **)& new);
		return (NULL);
	}
	i = 0;
	j = 0;
	free(str);
	while (epur[i])
		subretransform(epur, new, &i, &j);
	new[j] = 0;
	free(epur);
	return (new);
}

char	*transform_string(char *str, int i, int j)
{
	char	*new;
	int		nbword;

	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (NULL);
	nbword = many_nb(str);
	while (str[i])
	{
		if (str[i] && is_in_charset(str[i], "|"))
			nbword = many_nb(&str[i] + 1);
		if (str[i] == VARVIDE && nbword == 0)
		{
			new[j++] = VARVIDE;
			i++;
		}
		else if (str[i] == VARVIDE)
			i++;
		else if (str[i])
			new[j++] = str[i++];
	}
	new[j] = 0;
	return (retransform(new));
}
