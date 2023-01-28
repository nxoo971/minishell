/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 07:26:27 by jewancti          #+#    #+#             */
/*   Updated: 2023/01/24 11:35:15 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

void	close_pipes(t_heredoc *tab, int read, int write, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (write && tab[i].pipe[1] != -1)
			close(tab[i].pipe[1]);
		if (read && tab[i].pipe[0] != -1)
			close(tab[i].pipe[0]);
	}
}

int	find_pipe(t_heredoc *tab, const char *limiter, int len)
{
	int	i;

	i = -1;
	if (!tab || !tab[0].limiter)
		return (-1);
	while (++i < len)
	{
		if (limiter == tab[i].limiter)
			break ;
	}
	return (tab[i].pipe[0]);
}

void	print_heredoc(char *str, int fd, int exp, t_data *data)
{
	char	*var;
	int		i;

	i = 0;
	if (!exp)
		ft_putendl_fd(str, fd);
	else
	{
		while (str[i])
		{
			if (str[i] == '$' && str[i + 1] && is_variable(str[i + 1], 1))
			{
				var = expand(data, &str[i + 1]);
				if (var)
				{
					i += get_varname_len(&str[i + 1]);
					ft_putstr_fd(var, fd);
				}
			}
			else
				ft_putchar_fd(str[i], fd);
			i++;
		}
	}
	ft_putchar_fd('\n', fd);
}
