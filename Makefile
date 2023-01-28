#===============================================================================#
#								SOURCES											#
#===============================================================================#

INIT_DIR	= init
BLTS_DIR	= builtins
PARSE_DIR	= parse
ENV_DIR		= $(PARSE_DIR)/env
WILD_DIR		= $(PARSE_DIR)/wildcards
EXPAND_DIR	= $(PARSE_DIR)/expand
SIGNAL_DIR	= signal
EXEC_DIR	= exec
FREE_DIR	= free

INIT_DIRS	= $(INIT_DIR)\
			$(BLTS_DIR)\
			$(PARSE_DIR)\
			$(ENV_DIR)\
			$(EXPAND_DIR)\
			$(SIGNAL_DIR)\
			$(EXEC_DIR)\
			$(FREE_DIR)\
			$(WILD_DIR)\
			

SRC_FILES =	$(addprefix parse/, \
				parse.c			parse_input.c		utils_parse_input.c			utils.c		parse_heredoc.c		parse_here2.c \
				to_positive.c) \
			$(addprefix parse/env/, \
				t_env_init.c	t_env.c				t_env_utils.c) \
			$(addprefix parse/expand/, \
				expand.c		splitquote.c		cleanstring.c				add_expand_to_str.c\
				neg_chars.c		varvide.c) \
			$(addprefix builtins/, \
				cd.c			pwd.c				export.c					unset.c \
				echo.c			exit.c				is_builtin.c) \
			$(addprefix signal/, \
				ctrlc.c) \
			$(addprefix init/, \
				init_data.c) \
			$(addprefix exec/, \
				exec.c			sub_exec.c			is_heredoc.c		is_redirection.c			valid_command.c \
				heredoc_utils.c) \
			$(addprefix free/, \
				free.c) \
			main.c print.c playstation.c


#INIT = $(addsuffix .c, $(SRC_FILES))

 #=============================================================================#
#									OBJETS										#
 #=============================================================================#

OBJS_DIR = objets
OBJS = $(SRC_FILES:%.c=$(OBJS_DIR)/%.o)
DEPS = $(SRC_FILES:%.c=$(OBJS_DIR)/%.d)

 #=============================================================================#
#									LIBRARY										#
 #=============================================================================#

LIB_DIR = libft

 #=============================================================================#
#									COMPILATION									#
 #=============================================================================#

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror
CDFLAGS = -MMD -MP
CIFLAGS = -Iincludes -I$(LIB_DIR)/includes
CLFLAGS = -L$(LIB_DIR) -lft -lreadline

 #=============================================================================#
#									MAKEFILE									#
 #=============================================================================#

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(CIFLAGS) $(OBJS) $(CLFLAGS) -o $(NAME)

$(OBJS_DIR) :
	$(MAKE) -C $(LIB_DIR)
	mkdir $(OBJS_DIR)
	mkdir $(OBJS_DIR)/$(INIT_DIR)
	mkdir $(OBJS_DIR)/$(BLTS_DIR)
	mkdir $(OBJS_DIR)/$(PARSE_DIR)
	mkdir $(OBJS_DIR)/$(ENV_DIR)
	mkdir $(OBJS_DIR)/$(EXPAND_DIR)
	mkdir $(OBJS_DIR)/$(SIGNAL_DIR)
	mkdir $(OBJS_DIR)/$(EXEC_DIR)
	mkdir $(OBJS_DIR)/$(FREE_DIR)
	mkdir $(OBJS_DIR)/$(WILD_DIR)

$(OBJS) : $(OBJS_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(CDFLAGS) $(CIFLAGS) -c $< -o $@

clean :
	$(MAKE) clean -C $(LIB_DIR)
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	rm -rf $(NAME)

re : fclean all

-include $(DEPS)

.PHONY: all clean fclean re

#.SILENT: