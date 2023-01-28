/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:41:08 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/28 16:54:25 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tenv(t_env *ptr)
{
	t_env	*tmp;

	while (ptr)
	{
		tmp = ptr -> next;
		ft_memdel((void **)& ptr -> key);
		ft_memdel((void **)& ptr -> value);
		ft_memdel((void **)& ptr);
		ptr = tmp;
	}
	free(ptr);
}

void	free_cmd(t_cmd *ptr)
{
	t_cmd	*cmd;
	t_cmd	*cmd_tmp;
	int		i;

	cmd = ptr;
	while (cmd)
	{
		i = -1;
		cmd_tmp = cmd -> next;
		ft_memdel((void **)& cmd -> command);
		ft_arraydel(cmd -> args);
		while (++i < cmd -> length_sequence)
			ft_memdel((void **)& cmd -> sequence[i].redirect);
		ft_memdel((void **)& cmd -> sequence);
		ft_memdel((void **)& cmd);
		cmd = cmd_tmp;
	}
	ptr = 0;
}

void	free_heredoc(t_heredoc *heredoc, const int size)
{
	if (size == 0)
		return ;
	ft_memdel((void **)& heredoc);
}

void	free_shell(t_data *data)
{
	if (data -> dupt != -1)
		close(data -> dupt);
	ft_arraydel(data -> path);
	ft_arraydel(data -> env);
	ft_arraydel(data -> herecopy);
	free_tenv(data -> tenv);
	free_cmd(data -> cmd);
	free_heredoc(data -> here_doc, data -> len_here);
	data -> here_doc = 0;
	data -> herecopy = 0;
	data -> len_here = 0;
	data -> cmd = 0;
	data -> tenv = 0;
	data -> path = 0;
	data -> env = 0;
}
