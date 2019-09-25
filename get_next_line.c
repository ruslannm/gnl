/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/09/25 19:34:45 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libft.h>



char	*ft_get_buff(int fd, int *res)
{
	char	    buff[BUFF_SIZE + 1];
	static char *tail;
	int		    size;
	size_t      buff_bytes;
	char         *ret;

	if (tail && tail[0] != 0)
	{
		ret = ft_strdup(tail);
		size = ft_strlen(ret);
	}
	else
	{
		ret = (char *) malloc(sizeof(char) * (BUFF_SIZE + 1));
		size = 0;
		ret[0] = 0;
	}
	while (*res == 2)
	{
		if ((buff_bytes = read(fd, buff, BUFF_SIZE)) >= 0)
		{
			size += buff_bytes;
			ft_strlcat(ret, buff, size + 1);
			if ((tail = (char *) ft_memchr(ret, '\n', ft_strlen(ret))))
			{
				ret[tail - ret] = '\0';
				tail = tail + 1;
				*res = 1;
			} else if (buff_bytes < BUFF_SIZE)
				*res = 0;
			else
			{
				tail = ft_strdup(ret);
				free(ret);
				ret = (char *) malloc(sizeof(char) * (size_t) (size + BUFF_SIZE + 1));
				ret = ft_strcpy(ret, tail);
				free(tail);
			}
		}
	}
	return (ret);
}

int	get_next_line(const int fd, char **line)
{
	int res;

	if (fd < 0 || fd > 10240 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	res = 2;
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
