/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:10:34 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/19 08:01:48 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*new_env(char *key, char *value, int eq)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new -> key = key;
	new -> value = value;
	new -> equal = eq;
	new -> next = NULL;
	return (new);
}

void	add_back_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp -> next)
		tmp = tmp -> next;
	tmp -> next = new;
}
