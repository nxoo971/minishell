/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neg_chars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:03:52 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/26 18:50:36 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"
#define ISSPACEOPE "\t\v\n\r\f <>|"

static void	count_newlen2(char *s, int *i, int *len, t_data *data)
{
	(*i)++;
	while (s[*i] && s[(*i)] != '"')
	{
		if ((s[*i] == '$') && (s[*i + 1]) && (is_variable(s[*i + 1], 1)))
			*i += add_varlen_(data, &s[*i + 1], len);
		(*i)++;
		(*len)++;
	}
	(*i)++;
}

static int	count_newlen(t_data *data, char *s)
{
	int	i;
	int	len;
	int	lenstr;

	i = 0;
	len = 0;
	lenstr = ft_strlen(s);
	while (i < lenstr)
	{
		if (s[i] && s[i] == '"')
			count_newlen2(s, &i, &len, data);
		else if (s[i] == '\'' && len++)
		{
			while (s[++i] != '\'' && s[i])
				len++;
			i++;
		}
		else if ((i <= lenstr) && data->expand && (s[i] == '$') && (s[i + 1])
			&& (is_variable(s[i + 1], 1)))
				i += add_varlen_(data, &s[i + 1], &len) + 1;
		else
			i++;
		len++;
	}
	return (len);
}

static void	double_quote_check(char **dbl, int *i, int *j, t_data *data)
{
	char	*str;
	char	*new;

	str = dbl[0];
	new = dbl[1];
	if (str[*i + 1] == '"' && is_in_charset(str[*i + 2],
			ISSPACEOPE))
		new[(*j)++] = SLASHBACK;
	while (str[++(*i)] && str[*i] != '"')
	{
		if (data->expand && (str[*i] == '$') && (str[*i + 1])
			&& (is_variable(str[*i + 1], 1)))
			*i += add_value(new, &str[*i], data, j);
		else
			new[(*j)++] = find_char(str[*i]);
	}
	(*i)++;
}

static void	simple_quote_check(char *str, char *new, int *j, int *i)
{
	if (str[*i + 1] == '\'' && is_in_charset(str[*i + 2],
			ISSPACEOPE))
		new[(*j)++] = SLASHBACK;
	else
		while (str[++(*i)] && str[*i] != '\'')
			new[(*j)++] = find_char(str[*i]);
	(*i)++;
}

char	*negative_chars(char *s, t_data *data, int size)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (count_newlen(data, s) + 2));
	if (!new || !s)
		return (NULL);
	while (i < size && s[i])
	{
		if (s[i] == '"')
			double_quote_check((char *[2]){s, new}, &i, &j, data);
		else if (s[i] == '\'')
			simple_quote_check(s, new, &j, &i);
		else if (data->expand && s[i] == '$' && s[i + 1]
			&& is_variable(s[i + 1], 1))
			i += add_value_nospace(new, s + i, data, &j) + 1;
		else if ((s[i] == '$' && s[i + 1]) && is_in_charset(s[i + 1], "\"'"))
			i++;
		else
			new[j++] = s[i++];
	}
	new[j] = 0;
	return (new);
}
