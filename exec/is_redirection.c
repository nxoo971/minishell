/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 23:18:11 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/26 20:05:51 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

static
void	dup_or_printerr(const int fd, const int redirect)
{
	if (fd < 0)
		ft_putendl_fd("Cannot open file", 2);
	else if (fd > 2)
	{
		dup2(fd, redirect);
		close(fd);
	}
}

static
int	open_file(t_data *data, t_cmd *ptr,
	const int index_sequence)
{
	static const int	flags[3] = {
		O_WRONLY | O_CREAT | O_TRUNC, O_WRONLY | O_CREAT | O_APPEND,
		O_RDONLY
	};
	int					index_redirect;
	int					fd;

	fd = -1;
	index_redirect = ptr -> sequence[index_sequence].index_redirect;
	if (index_redirect != DLESS \
			&& ptr -> sequence[index_sequence].redirect[0] != VARVIDE)
		fd = open(ptr -> sequence[index_sequence].redirect, \
			flags[index_redirect - 1], 0666);
	if (index_redirect == DLESS && data -> len_here != 0)
		fd = find_pipe(data -> here_doc, \
			ptr -> sequence[index_sequence].redirect, data -> len_here);
	if (fd < 0)
	{
		if (ptr -> sequence[index_sequence].redirect[0] != VARVIDE)
			perror(ptr -> sequence[index_sequence].redirect);
		free_shell(data);
		return (-2);
	}
	return (fd);
}

int	is_redirection(t_data *data, t_cmd *ptr)
{
	int					fd;
	int					i;
	int					j;

	i = 0;
	j = 0;
	while (i < ptr -> length_sequence)
	{
		if (ptr -> sequence[i].redirect != NULL)
		{
			fd = open_file(data, ptr, i);
			if (fd == -2)
				return (EXIT_FAILURE);
			j++;
			if (ptr -> sequence[i].index_redirect != LESS \
				&& ptr -> sequence[i].index_redirect != DLESS)
				dup_or_printerr(fd, STDOUT_FILENO);
			else
				dup_or_printerr(fd, STDIN_FILENO);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
