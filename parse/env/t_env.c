/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferradi <rferradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 07:59:57 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/23 08:08:47 by rferradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

char	*get_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*get_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	return (ft_substr(str, i, ft_strlen(str)));
}

t_env	*copy_tenv(char **env)
{
	int		i;
	t_env	*new;
	char	path[4096];

	i = -1;
	new = new_env(ft_strdup("?"), ft_strdup("0"), 0);
	getcwd(path, 4096);
	ft_strcpy(path, ft_strrchr(path, '/') + 1);
	add_back_env(& new, new_env(get_key("OLDPWD"), get_value(path), 1));
	while (env[++i])
		add_back_env(& new, new_env(get_key(env[i]), get_value(env[i]), 1));
	return (new);
}

int	tenv_to_env(t_data *data, char **env)
{
	int		i;

	data -> env = ft_calloc(sizeof(char *), ft_arraylen(env) + 1);
	if (!data -> env)
		return (EXIT_FAILURE);
	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
		{
			data -> path = ft_split(env[i] + 5, ':');
			if (!data -> path)
				return (EXIT_FAILURE);
		}
		data -> env[i] = ft_strdup(env[i]);
		if (!data -> env[i])
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
