SRCS	=	ft_striteri.c		ft_strtrim.c	ft_strmapi.c		ft_atoi.c			\
			ft_isalpha.c		ft_memchr.c		ft_strchr.c			ft_strlen.c			\
			ft_tolower.c		ft_bzero.c		ft_isascii.c 		ft_memcmp.c			\
			ft_strdup.c			ft_strncmp.c	ft_toupper.c		ft_calloc.c			\
			ft_isdigit.c		ft_memcpy.c		ft_strlcat.c		ft_strnstr.c		\
			ft_isalnum.c 		ft_isprint.c	ft_memset.c			ft_memmove.c		\
			ft_strlcpy.c		ft_strrchr.c	ft_strnrchr.c		ft_substr.c			\
			ft_split.c			ft_strjoin.c	ft_itoa.c			ft_putchar_fd.c		\
			ft_putstr_fd.c		ft_putendl_fd.c	ft_putnbr_fd.c		ft_displaydouble.c

ADDED	=	ft_putchar.c		ft_putstr.c		ft_putnstr.c		ft_putnstr_fd.c \
			ft_putendl.c		ft_putnendl.c	ft_putnendl_fd.c	ft_putnbr.c		\
			ft_strcpy.c			ft_isspace.c	ft_swap.c			ft_strcmp.c		\
			ft_memdel.c			ft_arraydel.c	ft_strcat.c			ft_strsub.c		\
			ft_strncpy.c		ft_strstr.c		ft_strndup.c		ft_arraylen.c	\
			ft_atoull.c																											

BONUS	=	ft_lstnew.c			ft_lstadd_front.c	ft_lstsize.c	ft_lstlast.c	\
			ft_lstadd_back.c	ft_lstdelone.c		ft_lstclear.c	ft_lstiter.c	\
			ft_lstmap.c

GNL		=	$(addprefix ./get_next_line/,	get_next_line.c		get_next_line_utils.c)

PRINTF	=	$(addprefix ./ft_printf/,		ft_printf.c			extract_spec_info.c	\
			accept.c		explain_specification.c	algo_flag.c		exec_integer.c	\
			exec_octal.c	exec_binary.c			exec_unsigned.c	exec_double.c	\
			exec_string.c	calc_len.c				operations.c	color.c			\
			precision.c		print.c) 

NAME	=	libft.a

OBJS		= ${SRCS:.c=.o} ${ADDED:.c=.o} 

OBJS_BONUS	= ${BONUS:.c=.o}

OBJS_GNL	= ${GNL:.c=.o}

OBJS_PRINTF	= ${PRINTF:.c=.o}

HEADERS	= ./

.c.o	:
		cc -Wall -Wextra -Werror -I ${HEADERS} -c $< -o ${<:.c=.o}

${NAME} : $(OBJS) $(OBJS_BONUS) $(OBJS_GNL) $(OBJS_PRINTF)
		ar rcs $(NAME) $(OBJS) $(OBJS_BONUS) $(OBJS_GNL) $(OBJS_PRINTF)
		mkdir objs
		mv *.o objs

all : ${NAME}

bonus	: $(OBJS) $(OBJS_BONUS)
		ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

gnl		: $(OBJS_GNL)
		ar rcs $(NAME) $(OBJS_GNL)

printf	: $(OBJS_PRINTF)
		ar rcs $(NAME) $(OBJS_PRINTF)

any		: $(OBJS) $(OBJS_BONUS) $(OBJS_GNL) $(OBJS_PRINTF)
		ar rcs $(NAME) $(OBJS) $(OBJS_BONUS) $(OBJS_GNL) $(OBJS_PRINTF)

clean :
		rm -rf objs

fclean : clean
		rm -rf ${NAME}

re : fclean all
