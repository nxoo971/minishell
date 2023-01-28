/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:05:34 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/26 20:18:35 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define SIZEMATCH	7

int	matching(const char *match)
{
	static const char	*matchs[SIZEMATCH] = {
		"cd", "echo", "exit", "export", "pwd", "unset", "env"
	};
	int					i;

	i = 0;
	while (i < SIZEMATCH)
	{
		if (ft_strcmp(matchs[i], match) == 0)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

void	multiple_export_unset(t_cmd *cmd, t_data *data, int opt)
{
	int	i;

	i = 1;
	if (opt)
		while (cmd -> args[i])
			export(data, cmd -> args[i++], 0);
	else
		while (cmd -> args[i])
			unset(data, cmd -> args[i++]);
}

void	do_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp("cd", cmd -> command) == 0)
	{
		if (cmd -> args[1] && cmd -> args[2])
		{
			ft_putendl_fd("bash: cd: too many arguments", 2);
			return ;
		}
		if (ft_strcmp("cd", cmd -> args[0]) == 0 && cmd -> args[1])
			cd(data, cmd -> args[1]);
		else
			cd(data, "~");
	}
	else if (ft_strcmp("echo", cmd -> command) == 0)
		echo((const char **)cmd -> args + 1);
	else if (ft_strcmp("pwd", cmd -> command) == 0)
		pwd();
	else if (ft_strcmp("exit", cmd -> command) == 0)
		is_exit(data, cmd -> args);
	else if (ft_strcmp("export", cmd -> command) == 0)
		multiple_export_unset(cmd, data, 1);
	else if (ft_strcmp("unset", cmd -> command) == 0)
		multiple_export_unset(cmd, data, 0);
	else if (ft_strcmp("env", cmd -> command) == 0 && !cmd -> args[1])
		display_env(data-> tenv);
	update_status_code(data, data -> signal);
}

int	is_builtin(t_cmd *cmd)
{
	const char				*match;

	match = cmd -> command;
	if (!match)
		return (EXIT_FAILURE);
	return (matching(match));
}
