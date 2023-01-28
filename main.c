/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:47:36 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/26 19:59:17 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static
void	quit(short status, t_data *data)
{
	free_shell(data);
	rl_clear_history();
	ft_putendl_fd("exit", 2);
	exit(status);
}

static
int	check(int ac)
{
	if (ac != 1 || !isatty(STDIN_FILENO))
		return (EXIT_FAILURE);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, & ctrlc);
	return (EXIT_SUCCESS);
}

static
int	sub_main(t_data *data, const char *input, char **env, short *status)
{
	if (check_quote(input) == EXIT_SUCCESS)
	{
		if (init_data(data, env))
			return (EXIT_FAILURE);
		data -> expand = 1;
		parse_input(input, data -> cmd, data);
		data -> herecopy = split_iscote((char *)input);
		exec(data);
		*status = ft_atoi(get_key_from_tenv(data -> tenv, "?"));
		free_heredoc(data -> here_doc, data -> len_here);
		data -> here_doc = 0;
		data -> len_here = 0;
		free_cmd(data -> cmd);
		ft_arraydel(data -> path);
		data -> path = 0;
		ft_arraydel(data -> herecopy);
		data -> herecopy = 0;
		data -> cmd = 0;
	}
	else
		ft_putstr_fd("Syntax error\n", 2);
	return (EXIT_SUCCESS);
}

static
int	loop_shell(t_data *data, char **env, short *status)
{
	const char			*input;

	while (1)
	{
		input = readline("Fumier$ ");
		if (!input)
			quit(*status, data);
		if (*input)
			add_history(input);
		if (*input && check_chevrons(input) == EXIT_SUCCESS)
		{
			if (sub_main(data, input, env, status))
				return (EXIT_FAILURE);
		}
		else
			update_status_code(data, 2);
		ft_memdel((void **)& input);
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	static short		status = 0;
	t_data				*data;

	(void)av;
	if (check(ac))
		return (EXIT_FAILURE);
	ascii_start();
	data = starton();
	if (loop_shell(data, env, &status))
		return (EXIT_FAILURE);
	quit(status, data);
}
