/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:42:43 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/26 20:04:16 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static
void	attribute_args(int *start, int *index_args, char **parse, t_cmd *ptr)
{
	int		size_args;
	char	*str;

	size_args = get_length_args(parse);
	if (size_args > 0)
	{
		ptr -> args = ft_calloc(sizeof(char *), size_args + 1);
		while (parse[*start])
		{
			str = parse[*start];
			if (((str[0] == '>' || str[0] == '<' || str[0] == '|')
					&& str[1] == '\0')
				|| (ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0))
				break ;
			ptr -> args[(*index_args)++] = ft_strdup(parse[(*start)++]);
		}
	}
}

static
void	attribute_sequence(int *start, int *index_ar, char **parse, t_cmd *ptr)
{
	int	index_sequence;

	index_sequence = 0;
	if (!parse[*start + 1])
		return ;
	ptr -> sequence = ft_calloc(sizeof(t_sequence), ptr -> length_sequence);
	(*start)++;
	while (index_sequence < ptr -> length_sequence)
	{
		if (!parse[*start])
			return ;
		ptr->sequence[index_sequence].redirect
			= ft_strdup(parse[(*start)]);
		ptr->sequence[index_sequence++].index_redirect
			= get_index_redirect(parse[(*start) - 1]);
		if (parse[(*start)])
			(*start)++;
		while (parse[(*start)] && parse[(*start)][0] != '>'
			&& parse[(*start)][0] != '<'
			&& parse[(*start)][0] != '|')
			ptr -> args[(*index_ar)++] = ft_strdup(parse[(*start)++]);
		if (parse[(*start)] && (parse[(*start)][0] == '>'
			|| parse[(*start)][0] == '<'))
			(*start)++;
	}
}

static
void	setseq(t_cmd **ptr, char **arrays[2], int *index[3])
{
	char	**parse;
	char	**split;

	parse = arrays[0];
	split = arrays[1];
	if (parse[*index[0]])
	{
		(*ptr)->length_sequence = count_occurence(split[*index[2]], '>')
			+ count_occurence(split[*index[2]], '<');
		(*index[2])++;
	}
	else
		(*ptr)->length_sequence = 0;
	if ((*ptr)->length_sequence > 0)
		attribute_sequence(& *index[0], & *index[1], parse, (*ptr));
	while (parse[*index[0]] && parse[*index[0]][0] == '|')
		(*index[0])++;
	if (!(*ptr)->command && (*ptr)->args && (*ptr)->args[0])
		(*ptr)->command = ft_strdup((*ptr)->args[0]);
	if (parse[*index[0]])
	{
		(*ptr)->next = ft_calloc(sizeof(t_cmd), 1);
		(*ptr) = (*ptr)->next;
	}
}

int	loop(t_cmd **cmd, char **parse, char **split)
{
	t_cmd	*ptr;
	int		i;
	int		ind;
	int		arg;
	int		spl;

	ptr = *cmd;
	ind = 0;
	spl = 0;
	while (parse[ind])
	{
		i = 0;
		arg = 0;
		while (parse[ind][i] == '>' || parse[ind][i] == '<')
			i++;
		if (parse[ind][i] != '\0')
		{
			ptr -> command = ft_strdup(parse[ind]);
			if (!ptr -> command)
				return (EXIT_FAILURE);
		}
		attribute_args(& ind, & arg, parse, ptr);
		setseq(&ptr, (char **[2]){parse, split}, (int *[3]){&ind, &arg, &spl});
	}
	return (EXIT_SUCCESS);
}

int	parse_input(const char *input, t_cmd *cmd, t_data *data)
{
	char	**parse;
	char	*tmp;

	parse = clean_string((char *)input, data);
	if (!parse)
		return (EXIT_FAILURE);
	if (!parse || !parse[0])
	{
		if (!parse[0])
			free(parse);
		return (EXIT_SUCCESS);
	}
	tmp = array_to_string(parse);
	if (!tmp)
	{
		ft_arraydel(parse);
		return (EXIT_FAILURE);
	}
	return (sub_parse_input(cmd, parse, tmp));
}
