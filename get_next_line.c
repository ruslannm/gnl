/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/09/25 17:16:35 by rgero            ###   ########.fr       */
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
	size_t      buff_bytes;

	if (tail && tail[0] != 0)
	{
		ret = ft_strdup(tail);
		size = ft_strlen(ret);
	}
	else
	{
		ret = (char *) malloc(sizeof(char) * (buff_size + 1));
		size = 0;
		ret[0] = 0;
	}
	while ((buff_bytes = read(fd, buff, buff_size)))
	{
		size += buff_bytes;
		ft_strlcat(ret, buff, size +1);
		//ret[size] = '\0';
		free(tail);
		tail = (char *) malloc(sizeof(char) * (size + 1));
		if ((tail = ft_memchr(ret, '\n', ft_strlen(ret))))
		{
			ret[tail - ret + 1] = '\0';
			break;
		}
		else if (buff_bytes < buff_size)
			break; //end file
		else
		{
			tail = ft_strdup(ret);
			free(ret);
			ret = (char *) malloc(sizeof(char) * (size_t) (size + buff_size + 1));
			ret = ft_strcpy(ret, tail);
			//free(tail);
		}
	}
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
