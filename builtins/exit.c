/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:14:28 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/28 16:52:44 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define LLMAX	9223372036854775807LL
#define LLMIN	-9223372036854775807LL

int	no_args(char **argument)
{
	if (!argument || !*argument)
	{
		ft_putendl("exit");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static
void	end_exit(t_data *data, char **argument)
{
	int	ex;

	ft_putendl("exit");
	ex = 0;
	if (argument[1] != NULL)
		ex = ft_atoull(argument[1]) % 256;
	free_shell(data);
	exit(ex);
}

int	sub_exit(t_data *data, char *argument, char *b_argument, int *index[2])
{
	long long	res;

	res = ft_atoull(argument);
	if (*argument == '+' || *argument == '-')
		argument++;
	while (ft_isdigit(*argument))
	{
		(*index)[1]++;
		argument++;
	}
	if ((*index)[0] > 1)
	{
		ft_printf("exit\nbash: exit: too many arguments\n", argument);
		return (update_status_code(data, 127), EXIT_FAILURE);
	}
	if (*argument != '\0' || res > LLMAX || res < LLMIN)
	{
		if (!*argument)
			argument = b_argument;
		ft_printf("bash: exit: %s: numeric argument required\n", argument);
		free_shell(data);
		exit(2);
	}
	return (EXIT_SUCCESS);
}

void	is_exit(t_data *data, char **argument)
{
	int			index;
	int			index2;
	int			isdigit;
	int			retur;

	if (no_args(argument))
		return ;
	index = 0;
	isdigit = 0;
	while (argument[++index])
	{
		index2 = index;
		retur = sub_exit(data, argument[index], argument[index], \
							(int *[2]){& index2, & isdigit});
		if (retur)
			return ;
	}
	end_exit(data, argument);
}
