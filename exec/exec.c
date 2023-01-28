/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:52:38 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/28 16:53:45 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	close_fd(int (*fd)[2])
{
	if ((*fd)[0] != -1)
		close((*fd)[0]);
	if ((*fd)[1] != -1)
		close((*fd)[1]);
}

static
int	is_builtin_and_only_command(t_data *data)
{
	if (!data -> cmd -> next && is_builtin(data -> cmd) == EXIT_SUCCESS)
	{
		data -> dupt = dup(STDOUT_FILENO);
		if (is_redirection(data, data -> cmd))
			return (EXIT_FAILURE);
		do_builtin(data -> cmd, data);
		dup2(data -> dupt, STDOUT_FILENO);
		close(data -> dupt);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static
void	wait_pids(t_data *data, int index_pid)
{
	static int	rayan = 0;
	int			i;

	i = -1;
	while (++i < index_pid)
	{
		waitpid(data -> pids[i], & data -> signal, 0);
		if (WIFEXITED(data -> signal))
			data -> signal = WEXITSTATUS(data -> signal);
		if (data -> signal == 131 && !rayan++)
			ft_putendl_fd("Quit (core dumped)", 2);
	}
	rayan = 0;
	signal(SIGINT, & ctrlc);
	update_status_code(data, data -> signal);
}

static
void	loop_exec(t_data *data, int *index_pid)
{
	t_cmd	*ptr;

	ptr = data -> cmd;
	while (ptr)
	{
		if (pipe(data -> pipes) < 0)
			return ;
		signal(SIGINT, SIG_IGN);
		data -> pids[*index_pid] = fork();
		if (data -> pids[*index_pid] == -1)
		{
			close_fd(& data -> pipes);
			free_shell(data);
			exit(EXIT_FAILURE);
		}
		if (data -> pids[*index_pid] == 0)
			is_child(data, ptr, *index_pid);
		else
			is_father(data, *index_pid);
		(*index_pid)++;
		ptr = ptr -> next;
	}
	close(data->pipes[0]);
}

void	exec(t_data *data)
{
	t_cmd		*ptr;
	int			index_pid;

	ptr = data -> cmd;
	data -> signal = 0;
	index_pid = 0;
	is_heredoc(data, ptr);
	update_status_code(data, data -> signal);
	set_path_from_tenv(data);
	if (is_builtin_and_only_command(data) == EXIT_SUCCESS)
		return ;
	loop_exec(data, & index_pid);
	if (data -> len_here != 0)
		close_pipes(data -> here_doc, 1, 0, data -> len_here);
	wait_pids(data, index_pid);
	close_fd(& data -> pipes);
}
