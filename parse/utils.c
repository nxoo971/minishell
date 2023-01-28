/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 06:37:10 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/24 17:59:57 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_lstcount(t_cmd *cmd)
{
	t_cmd	*ptr;
	int		i;

	ptr = cmd;
	i = 0;
	while (ptr)
	{
		i++;
		ptr = ptr -> next;
	}
	return (i);
}

int	is_in_charset(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i] && charset[i] != c)
		;
	return (c == charset[i]);
}

int	error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}
