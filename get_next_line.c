/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/09/29 16:45:11 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_str_split_end(char **tail, int *res, ssize_t buff_bytes)
{
	int seek;
	int len;
	char *seekchr;
	char *tmp;
	char *ret;

	ret = NULL;
	len = ft_strlen(*tail);
	if ((seekchr = ft_memchr (*tail, '\n', len)))
	{
		seek = seekchr - *tail;
		ret = ft_strsub(*tail, 0, seek);
		if ((len - seek) == 1)
			ft_memdel((void **)&(*tail));
		else
		{
			tmp = ft_strsub(*tail, seek + 1, len - seek);
			ft_memdel((void **)&(*tail));
			*tail = ft_strdup(tmp);
			free(tmp);
		}
		*res = (*res == 0 ? 0 : 1);
	}
	else if (buff_bytes < BUFF_SIZE && *res >= 1)
	{
		ret = ft_strdup(*tail);
		ft_memdel((void **)&(*tail));
		*res = 1;
	}
	else if (*res == 0)
		ft_memdel((void **)&(*tail));
	return (ret);
}

char	*ft_get_buff(int fd, int *res)
{
	char	    buff[BUFF_SIZE];
	static char *tail;
	int		    size[2];
	ssize_t      buff_bytes;
	char         *ret;

	size[0] = 0;
	if (tail && tail[0] != '\0')
	{
		if ((ret = ft_str_split_end(&tail, &(*res), BUFF_SIZE)))
			return (ret);
	}
	else
		tail = (char *) ft_memalloc(sizeof(char)*(BUFF_SIZE + 1));
	while (*res > 1)
	{
		if ((buff_bytes = read(fd, buff, BUFF_SIZE)) > 0)
		{
			size[0] += buff_bytes;
			ft_strlcat(tail, buff, ft_strlen(tail) + buff_bytes + 1);
			ft_bzero(buff, BUFF_SIZE);
			if (ft_memchr(tail, '\n', ft_strlen(tail)) || buff_bytes < BUFF_SIZE)
				*res = *res - 1;
			else
			{
				ret = ft_strdup(tail);
				ft_memdel((void **)&tail);
				//tail[0] = '\0';
				//free(tail);
				tail = (char *) ft_memalloc(sizeof(char) * (ft_strlen(ret) + BUFF_SIZE + 1));
				tail = ft_strcpy(tail, ret);
				ft_memdel((void **)&ret);
				//free(ret);
			}
		}
		else if (buff_bytes == -1)
		{
			*res = -1;
			return(NULL);
		}
		else
			*res = (tail == NULL || tail[0] == '\0' ? 0 : 1);
	}
	ret = ft_str_split_end(&tail, &(*res), buff_bytes);
	if (ret)
		free(ret);
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
