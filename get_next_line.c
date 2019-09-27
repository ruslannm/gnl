/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/09/27 18:13:40 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libft.h>

int ft_str_split_end(char **ret, char **tail)
{
	int seek;
	int res;
	int len;
	char *seekchr;
	char *tmp;

	res = 0;
	seek = 0;
	len = ft_strlen(*tail);
	if ((seekchr = ft_memchr (*tail, '\n', len)))
	{
		seek = seekchr - *tail;
		*ret = ft_strsub(*tail, 0, seek);
		tmp = ft_strsub(*tail, seek + 1, len - seek);
        free(*tail);
		*tail = ft_strdup(tmp);
        free(tmp);
		res=1;
	}
	else
		res=0;
	return (res);
}

char	*ft_get_buff(int fd, int *res)
{
	char	    buff[BUFF_SIZE + 1];
	static char *tail;
	int		    size[2];
	size_t      buff_bytes;
	char         *ret;

	size[0] = 0;
	if (tail && tail[0] != 0)
		if (ft_str_split_end(ret, tail))
			return (ret);
	else
		ret = (char *) ft_memalloc(sizeof(char)*(BUFF_SIZE + 2));
	while (*res > 1)
	{
		if ((buff_bytes = read(fd, buff, BUFF_SIZE)) > 0)
		{
			size[0] += buff_bytes;
			ft_strlcat(ret, buff, size[0] + 1);
			if (buff_bytes < BUFF_SIZE)
				*res = 0; //end
			else
			{
				if (ft_memchr (ret, '\n', ft_strlen(ret)))
					*res = *res - 1;
				tail = ft_strdup(ret);
				free(ret);
				ret	= (char *)ft_memalloc(sizeof(char) * (size[0] + BUFF_SIZE + 1));
				ret = ft_strcpy(ret, tail);
				free(tail);
			}
		}
		else
			*res = 0;
	}
	return (ret);
}

int	get_next_line(const int fd, char **line)
{
	int res;

	if (fd < 0 || fd > 10240 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	res = 3;
	*line = ft_get_buff(fd, &res);
	return (res);
}

void	ft_read(int fd)
{
	char	*str;
	int i;

	i = get_next_line(fd, &str);
	if (str)
	{
		ft_putstr(str);
		ft_putstr("-");
		ft_putnbr(i);
		ft_putstr("-");
		i = get_next_line(fd, &str);
		ft_putstr(str);
		ft_putstr("-");
		ft_putnbr(i);
		ft_putstr("-");
		i = get_next_line(fd, &str);
		ft_putstr(str);
		ft_putstr("-");
		ft_putnbr(i);
		ft_putstr("-");

	}
	if (fd > 1)
		close(fd);
}
