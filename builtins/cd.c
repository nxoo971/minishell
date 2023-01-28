/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:01:50 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/26 17:41:33 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static
void	change_directory(t_data *data, const char *path)
{
	char	*str;
	char	*pwd;
	int		ret;

	ret = chdir(path);
	if (ret == -1)
	{
		perror(path);
		data -> signal = 1;
		return ;
	}
	pwd = pwd_malloc();
	if (!pwd)
		return ;
	str = ft_strjoin("PWD=", pwd);
	if (!str)
	{
		ft_memdel((void **)& pwd);
		return ;
	}
	export(data, str, 0);
	ft_memdel((void **)& pwd);
	ft_memdel((void **)& str);
}

void	cd(t_data *data, const char *path)
{
	if ((!path || ft_strcmp(path, "~") == 0) && getenv("HOME"))
		change_directory(data, getenv("HOME"));
	else
		change_directory(data, path);
}
