/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:26:47 by rferradi          #+#    #+#             */
/*   Updated: 2023/01/28 16:53:00 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CHARSET "<>| "
# define CHEVRON "<>"

# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define ISSPACE "\t\v\n\r\f "
# define VARVIDE 6

enum				e_redirect_index
{
	GREAT = 1,
	DGREAT,
	LESS,
	DLESS,
};

enum				e_operator
{
	PIPE = -1,
	CHEVRIGHT = -2,
	CHEVLEFT = -3,
	CHEVLEFTD = -4,
	CHEVRIGHTD = -5,
	SLASHBACK = -6
};

typedef struct s_sequence
{
	char			*redirect;
	int				index_redirect;
}					t_sequence;

typedef struct t_file
{
	char			*redirect;
	int				index_redirect;
}					t_file;

typedef struct s_cmd
{
	char			*command;
	char			**args;

	t_sequence		*sequence;
	int				length_sequence;

	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				equal;

	struct s_env	*next;
}					t_env;

typedef struct t_heredoc
{
	int				pipe[2];
	const char		*limiter;
	int				expand;
}					t_heredoc;

typedef struct s_data
{
	t_env			*tenv;
	t_cmd			*cmd;
	pid_t			pids[4096];

	int				pipes[2];
	int				dupt;
	int				prev_pipe;
	char			**path;
	char			**env;
	t_list			*dir;

	t_heredoc		*here_doc;
	int				len_here;

	char			**herecopy;
	int				expand;
	int				signal;

	struct t_data	*next;
}					t_data;

/*
	DIRECTORY: ./SRC

*/
//	init_data.c
int					init_data(t_data *data, char **env);

//	PARSE HEREDOC
int					countlen(char *str);
int					lenword(char *str);
char				**split_iscote(char *str);
void				find_here_doc(char **here, t_data *data);

//	STARTON
t_data				*starton(void);

/*
	DIRECTORY: ./PARSE

		./
*/
//	parse.c
int					check_quote(const char *str);
int					check_chevrons(const char *str);
char				**split_iscote(char *str);
//	parse_input.c
int					parse_input(const char *input, t_cmd *cmd, t_data *data);
int					loop(t_cmd **cmd, char **parse, char **split);
int					sub_parse_input(t_cmd *cmd, \
										char **parse, char *tmp);
//	utils_parse_input.c
char				*array_to_string(char **array);
void				ft_realloc(char **line, const char *s1);
int					count_occurence(const char *str, const char c);
int					get_length_args(char **ptr);
int					get_index_redirect(const char *redirect);
//	to_positive.c
void				to_positive(t_cmd *cmd);
char				*positive_stringchar(char *str);
char				**positive_arraychars(char **str);
//	utils.c
int					ft_lstcount(t_cmd *cmd);
int					is_in_charset(char c, char *charset);
int					error_msg(char *str);
//	parse_heredoc.c
void				find_here_doc(char **here, t_data *data);

/*
	DIRECTORY: ./PARSE

		./env
*/
//	t_env_init.c
t_env				*new_env(char *key, char *value, int eq);
void				add_back_env(t_env **env, t_env *new);
//	t_env.c
t_env				*copy_tenv(char **env);
char				*get_key(char *str);
char				*get_value(char *str);
int					tenv_to_env(t_data *data, char **env);

//	t_env_utils.c
char				*get_key_from_tenv(t_env *tenv, const char *key);
void				set_path_from_tenv(t_data *data);
void				update_status_code(t_data *data, short code);
/*
	DIRECTORY: ./PARSE

		./expand
*/
//	expand.c
char				*expand(t_data *data, const char *var);
size_t				get_varvalue_len(t_data *data, const char *var);
size_t				is_variable(const char c, int opt);
size_t				get_varname_len(const char *var);
// varvide.c
char				*transform_string(char *str, int i, int j);
//	clean_string.c
char				**clean_string(char *str, t_data *data);
char				*putspace_between_operateur(char *str, int j);
void				positive_chars(char **str);
//	split_quote.c
char				**split_quote(char const *s, char *charset);
//	add_expand_to_str.c
int					add_varlen_(t_data *data, char *str, int *len);
int					add_value(char *new, char *str, t_data *data, int *j);
int					add_value_nospace(char *new, char *str, t_data *data,
						int *j);
//	neg_chars.c
char				*negative_chars(char *str, t_data *data, int size);
int					find_char(char c);

char				*positive_stringchar(char *str);

/*
	DIRECTORY: ./BUILTINS
*/
//	is_builtin.c
int					is_builtin(t_cmd *cmd);
void				do_builtin(t_cmd *cmd, t_data *data);
int					matching(const char *match);
//	is_exit.c
void				is_exit(t_data *data, char **argument);
//	pwd.c
void				pwd(void);
char				*pwd_malloc(void);
//	cd.c
void				cd(t_data *data, const char *path);
//	unset.c
void				unset(t_data *data, const char *key);
//	echo.c
void				echo(const char **arg);
//	export.c
void				export(t_data *data, const char *str, int force);

/*
	DIRECTORY: ./EXEC
*/
//	exec.c
void				exec(t_data *data);
void				close_fd(int (*fd)[2]);
//	sub_exec.c
void				is_child(t_data *data, t_cmd *ptr, int index_pid);
void				is_father(t_data *data, int index_pid);
//	is_heredoc.c
void				is_heredoc(t_data *data, t_cmd *cmd);
//	heredoc_utils.c
void				close_pipes(t_heredoc *tab, int read, int write, int len);
void				print_heredoc(char *str, int fd, int exp, t_data *data);
int					find_pipe(t_heredoc *tab, const char *limiter, int len);

//	is_redirection.c
int					is_redirection(t_data *data, t_cmd *ptr);
//	valid_command.c
char				*valid_command(const char *command, char **env);

/*
	DIRECTORY: ./SIGNAL
*/
//	signal.c
void				ctrlc(int sig);
void				reactiv(int sig);

/*
	DIRECTORY: ./
*/
//	print.c
void				print_cmd(t_cmd *cmd);
void				display_lst(t_list *lst);
void				display_env(t_env *env);
/*
	DIRECTORY: ./free
*/
//	free.c
void				free_shell(t_data *data);
void				free_cmd(t_cmd *ptr);
void				free_tenv(t_env *ptr);
void				free_heredoc(t_heredoc *heredoc, const int size);

void				ascii_start(void);
t_data				*starton(void);
t_cmd				*lstlast(t_cmd *cmd);

#endif
