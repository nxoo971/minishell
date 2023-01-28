/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_expand_to_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:17:14 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/26 17:21:12 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

int	add_varlen_(t_data *data, char *str, int *len)
{
	*len += get_varvalue_len(data, str);
	return (get_varname_len(str));
}

int	add_value(char *new, char *str, t_data *data, int *j)
{
	int		i;
	char	*var;

	i = -1;
	var = expand(data, str + 1);
	if (!var || !*var)
	{
		new[(*j)++] = VARVIDE;
		return (get_varname_len(str + 1));
	}
	while (var[++i])
	{
		if (ft_isspace(var[i]))
			new[*j] = var[i] * -1;
		else if (var[i] == '|')
			new[*j] = PIPE;
		else
			new[*j] = var[i];
		*j += 1;
	}
	return (get_varname_len(str + 1));
}

int	add_value_nospace(char *new, char *str, t_data *data, int *j)
{
	int		i;
	char	*var;

	i = -1;
	var = expand(data, str + 1);
	if (!var || !*var)
	{
		new[(*j)++] = VARVIDE;
		return (get_varname_len(str + 1));
	}
	var = ft_strtrim(var, ISSPACE);
	while (var[++i])
	{
		if (ft_isspace(var[i]))
		{
			while (var[i] && ft_isspace(var[i]))
				i++;
			new[(*j)++] = ' ';
			i--;
		}
		else
			new[(*j)++] = find_char(var[i]);
	}
	free(var);
	return (get_varname_len(str + 1));
}
