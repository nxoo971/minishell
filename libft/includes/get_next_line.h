/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:23:09 by ooxn              #+#    #+#             */
/*   Updated: 2022/12/08 23:15:20 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include "libft.h"

# define BUFFER_SIZE	4096

char	*get_next_line(int fd, int destroy);
char	*ft_strdupcpy(char *d1, char *s1, char *s2, int n);
int		readuntil(char **bufferline, int fd);
void	ft_freetab(char ***ptr, int force);

#endif
