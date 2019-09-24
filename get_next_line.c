/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/09/24 18:01:52 by rgero            ###   ########.fr       */
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
	static char *str;
	char	    *temp;
	int		    size;
	size_t      seek;
	size_t      buff_bytes;

	size = 0;
	if (str == NULL)
	{
		str = (char*)malloc(sizeof(char) * (size + 1));
		str[0] = 0;
	}
	temp = (char*)malloc(sizeof(char) * (size + 1));
	temp[0] = 0;
	while ((buff_bytes = read(fd, buff, buff_size)) && str && temp )
	{
		size += buff_bytes;
		ft_strcpy(temp, str);
		free(str);
		str = (char*)malloc(sizeof(char) * (size + 1));
		ft_strcpy(str, temp);
		ft_strlcat(str, buff, size +1);
		str[size] = '\0';
		free(temp);
		temp = (char*)malloc(sizeof(char) * (size + 1));
		ft_stop_read(&size, buff_bytes);
		seek = size - buff_bytes;
		while (seek < buff_bytes && buff[seek] != '\n')
			seek++;
		if (buff[seek] == '\n')
			break;
	}
	free(temp);
	temp = (char*)malloc(sizeof(char) * (seek + 1));
	ft_strncpy(temp, str, seek + 1);
	str = ft_strsub(str,seek + 1, size - seek);
	return (temp);
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
	}
	if (fd > 1)
		close(fd);
}
