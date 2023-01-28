/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:35:41 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/24 19:59:24 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static
int	is_valid_name(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (*str == '=' || ft_isdigit(*str))
		return (ft_printf("export: `%s' not a valid identifier\n", str) < 0);
	while (str[i] && str[i] != '=')
	{
		if (!is_variable(str[i], 0))
			return (ft_printf("export: `%s' not a valid identifier\n", str) < 0);
		i++;
	}
	return (1);
}

static
int	isset_var(t_env *temp, char *name, char *value)
{
	if (temp -> key && ft_strcmp(temp -> key, name) == 0)
	{
		if (value)
		{
			ft_memdel((void **)& temp -> value);
			temp -> value = value;
			ft_memdel((void **)& name);
			return (0);
		}
	}
	return (1);
}

static
void	make_export(t_data *data, char *name, char *value, int eq)
{
	t_env	*temp;

	temp = data -> tenv;
	if (!data->tenv)
		return ;
	while (temp && temp -> next)
	{
		if (!isset_var(temp, name, value))
			return ;
		temp = temp -> next;
	}
	if (!isset_var(temp, name, value))
		return ;
	add_back_env(&data->tenv, new_env(name, value, eq));
}

void	export(t_data *data, const char *str, int force)
{
	size_t	len;
	char	*varname;
	char	*value;

	len = get_varname_len(str);
	if (force == 0 && !is_valid_name(str))
		return ;
	varname = ft_substr(str, 0, len);
	if (!varname)
		return ;
	value = ft_substr(str, len + 1, ft_strlen(str) - len);
	if (!value)
	{
		ft_memdel((void **)& varname);
		return ;
	}
	make_export(data, varname, value, ft_strchr(str, '=') == 0);
}
