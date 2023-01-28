/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanstring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 01:26:17 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/26 19:19:04 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

char	**clean_string(char *str, t_data *data)
{
	char	**clean;
	char	*neg;
	char	*ope;
	char	*trans;

	neg = negative_chars(str, data, ft_strlen(str));
	if (!neg)
		return (NULL);
	ope = putspace_between_operateur(neg, 0);
	ft_memdel((void **)&neg);
	if (!ope)
	{
		ft_memdel((void **)&neg);
		return (NULL);
	}
	trans = transform_string(ope, 0, 0);
	ft_memdel((void **)&ope);
	clean = split_quote(trans, ISSPACE);
	ft_memdel((void **)&trans);
	positive_chars(clean);
	return (clean);
}

static
int	count_ope(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((i > 0) && (str[i] && is_in_charset(str[i], "|<>")
				&& !is_in_charset(str[i - 1], "|<>")))
			count += 2;
		if (str[i] && is_in_charset(str[i], "|<>"))
			count += 2;
		i++;
	}
	return (count + i + 2);
}

char	*putspace_between_operateur(char *str, int j)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(sizeof(char) * (count_ope(str) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] && (str[i] > 0 || str[i] == VARVIDE)
			&& is_in_charset(str[i], "|<>"))
		{
			new[j++] = ' ';
			if ((!ft_strncmp(&str[i], ">>", 2)
					|| !ft_strncmp(str + i, "<<", 2)) && str[i + 1])
				new[j++] = str[i++];
			if (str[i])
				new[j++] = str[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = str[i++];
	}
	new[j] = 0;
	return (new);
}

void	positive_chars(char **str)
{
	int	i;
	int	j;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if ((str[i][j] <= -9 && str[i][j] >= -13) || str[i][j] == -32)
				str[i][j] = (str[i][j] * -1);
		}
	}
}

int	find_char(char c)
{
	if (ft_isspace(c))
		return (c * -1);
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (CHEVLEFT);
	else if (c == '<')
		return (CHEVRIGHT);
	else
		return (c);
}

/*

< Makefile cat | ls

cat | ls > out

ls > out -R | cat > out

ls -R > out -l

*/