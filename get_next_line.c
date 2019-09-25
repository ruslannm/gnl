/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/09/25 15:33:15 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libft.h>

# define MAX_INT 2147483647

int	get_next_line(const int fd, char **line)
{
	size_t buff_bytes;
	size_t seek;
	char buff[BUFF_SIZE];
	static char *tmp_line;
	char *tmp;

	if (tmp_line == 0)
	{
		while ((buff_bytes = read(fd, buff, BUFF_SIZE)))
		{
			buff[buff_bytes] = '\0';
			seek = 0;
			while (seek < buff_bytes || buff[seek] != '\n')
				seek++;
			tmp = (char *) malloc(sizeof(char) * (seek + 1));
			ft_strncpy(tmp, buff, seek + 1);
			tmp[seek - 1] = '\n';
			tmp[seek] = '\0';
		}
		*line = tmp;
	}
	return (1);
}

void	ft_stop_read(int *size, int buff_size)
{
	if (MAX_INT - buff_size < *size)
		*size = -1;
}

char	*ft_get_buff(int fd, int buff_size)
{
	char	    buff[buff_size + 1];
	static char *tail;
	char	    *ret;
	int		    size;
	char        *seek;
	size_t      buff_bytes;

	size = 0;
	if (tail && tail[0] != 0)
		size = ft_strlen(tail) ;
	else
	{
		tail = (char*)malloc(sizeof(char));
		tail[0] = 0;
	}
	ret = (char*)malloc(sizeof(char) * (buff_size + size + 1));
	ret[0] = 0;
	while ((buff_bytes = read(fd, buff, buff_size)))
	{
		size += buff_bytes;
		ft_strlcat(tail, buff, size +1);
//		str[size] = '\0';
		free(ret);
		if (ft_memchr(tail, '\n', ft_strlen(tail)))
		{
			seek = (char*)malloc(sizeof(char) *ft_strlen(tail));
			seek = ft_memchr(tail, '\n', ft_strlen(tail));
			ret = (char*)malloc(sizeof(char) * (size_t)(seek - tail + 1));
			ft_strncpy(ret, tail, seek -tail + 1);
			size = ft_strlen(tail) - seek;
			free(tail);
			tail = (char*)malloc(sizeof(char) * (size_t)(size + 1));
			ft_strncpy(tail, seek, ft_strlen(seek));
			free(seek);
			return (ret);
		}
		else
		{
			ret = (char *) malloc(sizeof(char) * (size_t) (size + 1));
		}
	}
	free(ret);
	ret = (char*)malloc(sizeof(char) * (size_t)(seek - tail + 1));
	ft_strncpy(ret, tail, (size_t )(seek + 1));
	tail = (char *)ft_memchr(tail,'\n', (size_t)(seek - tail + 1));
	return (ret);
}

void	ft_read(int fd)
{
	char	*str;

	str = ft_get_buff(fd, BUFF_SIZE);
	if (str)
	{

		ft_putstr(str);
		str = ft_get_buff(fd, BUFF_SIZE);
		ft_putstr(str);
		str = ft_get_buff(fd, BUFF_SIZE);
		ft_putstr(str);

	}
	if (fd > 1)
		close(fd);
}
