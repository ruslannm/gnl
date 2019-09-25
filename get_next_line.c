/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/09/24 19:50:18 by rgero            ###   ########.fr       */
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
	static char str[buff_size];
	char	    *temp;
	int		    size;
	char        *seek;
	size_t      buff_bytes;

	size = 0;
	if (str && str[0] != 0)
		size = ft_strlen(str) ;
	else
		str[0] = 0;
	temp = (char*)malloc(sizeof(char) * (size + 1));
	temp[0] = 0;
	while ((buff_bytes = read(fd, buff, buff_size)))
	{
		size += buff_bytes;
		ft_strcpy(temp, str);
		ft_strcpy(str, temp);
		ft_strlcat(str, buff, size +1);
//		str[size] = '\0';
		free(temp);
		if ((seek = ft_memchr(str, '\n', ft_strlen(str))))
		{
			temp = (char*)malloc(sizeof(char) * (size_t)(seek - str + 1));
			ft_strncpy(temp, str, seek -str + 1);
			str = seek + 1;
			return (temp);
		}
		else
			temp = (char*)malloc(sizeof(char) * (size_t)(size + 1));
	}
	free(temp);
	temp = (char*)malloc(sizeof(char) * (size_t)(seek - str + 1));
	ft_strncpy(temp, str, (size_t )(seek + 1));
	str = (char *)ft_memchr(str,'\n', (size_t)(seek - str + 1));
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
		str = ft_get_buff(fd, BUFF_SIZE);
		ft_putstr(str);

	}
	if (fd > 1)
		close(fd);
}
