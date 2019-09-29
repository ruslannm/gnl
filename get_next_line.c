/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/09/29 11:55:23 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_str_split_end(char **ret, char **tail, int noend)
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
		res = (noend == 0 ? 0 : 1);
	}
	else if (noend == 0)
	{
		*ret = ft_strdup(*tail);
		free(*tail);
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
	{
		if (ft_str_split_end(&ret, &tail, *res))
			return (ret);
	}
	else
		tail = (char *) ft_memalloc(sizeof(char)*(BUFF_SIZE + 2));
	while (*res > 1)
	{
		if ((buff_bytes = read(fd, buff, BUFF_SIZE)) > 0)
		{
			size[0] += buff_bytes;
			ft_strlcat(tail, buff, size[0] + 1);
			if (buff_bytes < BUFF_SIZE)
				*res = 0; //end
			else
			{
				if (ft_memchr (tail, '\n', ft_strlen(tail)))
					*res = *res - 1;
				ret = ft_strdup(tail);
				free(tail);
				tail = (char *)ft_memalloc(sizeof(char) * (size[0] + BUFF_SIZE + 1));
				tail = ft_strcpy(tail, ret);
				free(ret);
			}
		}
		else
			*res = 0;
	}
	ft_str_split_end(&ret, &tail, *res);
	//if (*res == 0)
	//	close(fd);
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
