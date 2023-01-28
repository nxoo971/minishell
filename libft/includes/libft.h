/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 20:13:10 by ooxn              #+#    #+#             */
/*   Updated: 2023/01/24 11:44:35 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
int			ft_lstsize(t_list *lst);

void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memchr(const void *s, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);

void		ft_bzero(void *s, size_t n);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

ssize_t		ft_putchar_fd(const char c, int fd);
ssize_t		ft_putstr_fd(const char *s, int fd);
ssize_t		ft_putendl_fd(const char *s, int fd);
ssize_t		ft_putnbr_fd(int n, int fd);

/* ajout en plus */
long long	ft_atoull(const char *str);
size_t		ft_arraylen(char **s);
ssize_t		ft_putchar(const char c);
ssize_t		ft_putstr(const char *s);
ssize_t		ft_putnstr(const char *s, size_t len);
ssize_t		ft_putnstr_fd(const char *s, size_t len, int fd);
ssize_t		ft_putendl(const char *s);
ssize_t		ft_putnendl(const char *s, size_t len);
ssize_t		ft_putnendl_fd(const char *s, size_t len, int fd);
int			ft_isspace(const char c);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strncpy(char *dest, const char *src, size_t n);
char		*ft_strcat(char *dst, const char *src);
char		*ft_strsub(const char *str, unsigned int start, size_t end);
char		*ft_strndup(const char *s1, size_t n);
char		*ft_strstr(const char *haystack, const char *needle);
void		ft_memdel(void **ptr);
void		ft_arraydel(char **ptr);
void		ft_putnbr(int n);
void		ft_swap(void *a, void *b, size_t const n);
/* ********** */

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);

char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnrchr(const char *s, int c, int len);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *str, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s1);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_itoa(int n);

int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi(const char *str);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

//	additionnel

void		ft_displaydouble(char **str);

#endif
