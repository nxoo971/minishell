/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:19:49 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/26 09:50:36 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

static
int	len_here_doc(t_cmd *ptr)
{
	int		len;
	int		i;
	t_cmd	*tmp;

	tmp = ptr;
	len = 0;
	while (tmp)
	{
		i = 0;
		while (i < tmp -> length_sequence)
		{
			if (tmp -> sequence[i].index_redirect == DLESS)
				len++;
			i++;
		}
		tmp = tmp -> next;
	}
	return (len);
}

static
int	set_tabs(t_heredoc *tab, t_cmd *ptr)
{
	t_cmd	*tmp;
	int		i;
	int		j;

	j = 0;
	tmp = ptr;
	while (tmp)
	{
		i = 0;
		while (i < tmp -> length_sequence)
		{
			if (tmp -> sequence[i].index_redirect == DLESS)
			{
				tab[j].limiter = tmp->sequence[i].redirect;
				if (pipe(tab[j++].pipe) == -1)
					return (EXIT_FAILURE);
			}
			i++;
		}
		tmp = tmp -> next;
	}
	return (EXIT_SUCCESS);
}

static
void	write_to_pipe(t_heredoc *tab, int len, t_data *data)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < len)
	{
		while (1)
		{
			line = readline("heredoc :");
			if (!line || !ft_strcmp(line, tab[i].limiter))
				break ;
			print_heredoc(line, tab[i].pipe[1], tab[i].expand, data);
		}
		ft_memdel((void **)& tab[i].limiter);
		if (tab[i].pipe[1] != -1)
			close(tab[i].pipe[1]);
		if (tab[i].pipe[0] != -1)
			close(tab[i].pipe[0]);
	}
}

static
void	exit_heredoc(int sig)
{
	t_data	*data;
	int		i;

	data = starton();
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		i = -1;
		while (++i < data -> len_here)
		{
			if (data -> here_doc[i].pipe[0] != -1)
				close(data -> here_doc[i].pipe[0]);
			if (data -> here_doc[i].pipe[1] != -1)
				close(data -> here_doc[i].pipe[1]);
			if (data -> here_doc[i].limiter != NULL)
				ft_memdel((void **)& data -> here_doc[i].limiter);
		}
		close_fd(& data -> pipes);
		free_shell(data);
		exit(130);
	}
}

void	is_heredoc(t_data *data, t_cmd *ptr)
{
	pid_t		pid;

	data -> len_here = len_here_doc(data -> cmd);
	data -> here_doc = ft_calloc(sizeof(t_heredoc), data -> len_here);
	if (!data -> here_doc)
		return ;
	signal(SIGINT, SIG_IGN);
	if (set_tabs(data -> here_doc, ptr))
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		signal(SIGINT, & exit_heredoc);
		find_here_doc(data -> herecopy, data);
		write_to_pipe(data -> here_doc, data -> len_here, data);
		free_shell(data);
		exit(EXIT_SUCCESS);
	}
	close_pipes(data -> here_doc, 0, 1, data -> len_here);
	waitpid(pid, & data -> signal, 0);
	if (WIFEXITED(data -> signal))
		data -> signal = WEXITSTATUS(data -> signal);
	signal(SIGINT, SIG_IGN);
}
