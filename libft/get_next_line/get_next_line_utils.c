/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                        		:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nxoo <nxoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:23:20 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/29 21:16:54 by nxoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_strdupcpy(char *d1, char *s1, char *s2, int n)
{
	char	*res;
	int		i;

	i = -1;
	if (!s2)
	{
		while ((++i < n && n != -1 && s1[i]) || (s1[i] && n == -1))
			d1[i] = s1[i];
		d1[i] = 0;
		return (d1);
	}
	if (n != -1)
		res = malloc(n + 1);
	else
	{
		while (s2[++i])
			;
		res = malloc(i + 1);
	}
	if (n == -1)
		return (ft_strdupcpy(res, s2, NULL, i));
	return (ft_strdupcpy(res, s2, NULL, n));
}

void	ft_freetab(char ***ptr, int force)
{
	int		i;
	int		res;

	if (!*ptr)
		return ;
	i = -1;
	res = 0;
	while (!force && (*ptr)[++i] != NULL)
	{
		if ((*ptr)[i][0] != '\0')
			res++;
	}
	if (res == 0)
	{
		i = -1;
		while ((*ptr)[++i] != NULL)
		{
			ft_memdel((void **)& (*ptr)[i]);
			(*ptr)[i] = NULL;
		}
		ft_memdel((void **)& *ptr);
		*ptr = NULL;
	}
}

void	ft_strnjoin(char **line, const char *s1, int size)
{
	char	*res;
	int		i;

	if (*line && **line)
	{
		i = 0;
		while ((*line)[i])
			i++;
		res = malloc(size + i + 1);
		if (res)
		{
			ft_strdupcpy(res, *line, NULL, -1);
			ft_strdupcpy(res + i, (char *)s1, NULL, -1);
			ft_memdel((void **)& *line);
			*line = res;
		}
		return ;
	}
	if (*line && !**line)
		ft_memdel((void **)& *line);
	*line = ft_strdupcpy(NULL, NULL, (char *)s1, -1);
}

int	readuntil(char **bufferline, int fd)
{
	char	buff[BUFFER_SIZE + 1];
	int		byteread;

	byteread = 1;
	while (byteread)
	{
		byteread = read(fd, buff, BUFFER_SIZE);
		if (byteread < 0)
			return (0);
		buff[byteread] = 0;
		if (byteread == 0)
			break ;
		ft_strnjoin(bufferline, buff, byteread);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (1);
}
