/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:39:16 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/24 11:35:35 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*path_cmd(const char *command)
{
	char	*joined;

	joined = ft_strdup(command);
	if (access(joined, F_OK) == -1)
		ft_printf("%s: No such file or directory\n", command);
	else if (access(joined, X_OK | R_OK) == -1)
		ft_printf("%s: Permission denied\n", command);
	else
		return (joined);
	ft_memdel((void **)& joined);
	return (NULL);
}

static char	*simple_cmd(const char *command, char **env)
{
	int		i;
	char	*joined;

	i = -1;
	while (command && env[++i])
	{
		joined = ft_strjoin(env[i], "/");
		ft_realloc(& joined, command);
		if (access(joined, X_OK) == 0)
			return (joined);
		ft_memdel((void **)& joined);
	}
	return (NULL);
}

char	*valid_command(const char *command, char **env)
{
	if (!command || !env)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (path_cmd(command));
	return (simple_cmd(command, env));
}
