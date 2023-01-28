/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:27:26 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/23 12:36:17 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#define ISSEP "\t\v\n\r\f <>|"

void	fill_tab2(char *str, char *quote, int *i, char *word)
{
	*quote = *str;
	word[(*i)++] = *str++;
	while (*str && *str != *quote)
		word[(*i)++] = *str++;
	word[(*i)++] = *str++;
}

char	*fill_tab(char **ptr)
{
	int		i;
	char	*word;
	char	quote;
	char	*str;

	str = *ptr;
	i = 0;
	word = malloc(sizeof(char) * (lenword(str) + 1));
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '"' || *str == '\'')
		fill_tab2(str, &quote, &i, word);
	else if (*str && is_in_charset(*str, "|><"))
	{
		word[i++] = *str++;
		if (word[i - 1] == *str)
			word[i++] = *str++;
	}
	else
		while (!is_in_charset(*str, ISSEP))
			word[i++] = *str++;
	word[i] = 0;
	*ptr = str;
	return (word);
}

char	**split_iscote(char *str)
{
	int		len;
	char	**new;
	int		i;

	i = -1;
	if (!str || !*str)
		return (NULL);
	len = countlen(str);
	if (len == 0)
		return (0);
	new = malloc(sizeof(char *) * (len + 1));
	while (++i < len)
		new[i] = fill_tab(&str);
	new[i] = 0;
	return (new);
}

char	*re_clean(char *str, t_data *data)
{
	char	*result;
	char	**cstring;

	cstring = clean_string(str, data);
	result = ft_strdup(*cstring);
	ft_arraydel(cstring);
	return (result);
}

void	find_here_doc(char **here, t_data *data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (!here || !*here)
		return ;
	data -> expand = 0;
	while (here[++i])
	{
		if (ft_strcmp(here[i], "<<") == 0)
		{
			i++;
			if (ft_strchr(here[i], '"') || ft_strchr(here[i], '\''))
				data->here_doc[count].expand = 0;
			else
				data->here_doc[count].expand = 1;
			data->here_doc[count].limiter = positive_stringchar(re_clean
					(here[i], data));
			count++;
		}
		if (!here[i])
			break ;
	}
	data -> expand = 1;
}
