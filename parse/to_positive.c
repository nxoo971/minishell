/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_positive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 08:55:41 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/24 12:18:57 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*positive_stringchar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == PIPE)
			str[i] = '|';
		if (str[i] == CHEVLEFT)
			str[i] = '>';
		if (str[i] == CHEVRIGHT)
			str[i] = '<';
		if (str[i] == SLASHBACK)
			str[i] = '\0';
	}
	return (str);
}

char	**positive_arraychars(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		positive_stringchar(str[i]);
	return (str);
}

void	to_positive(t_cmd *cmd)
{
	t_cmd	*ptr;
	int		i;

	ptr = cmd;
	i = -1;
	while (ptr)
	{
		if (ptr -> command)
			positive_stringchar(ptr -> command);
		if (ptr -> args)
			positive_arraychars(ptr -> args);
		while (++i < ptr -> length_sequence)
			positive_stringchar(ptr -> sequence[i].redirect);
		ptr = ptr -> next;
	}
}
