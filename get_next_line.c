/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/09/30 18:49:37 by rgero            ###   ########.fr       */
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
			tmp = ft_strsub(*tail, seek + 1, len - seek - 1);
			ft_memdel((void **)&(*tail));
			*tail = ft_strdup(tmp);
			ft_memdel((void **)&tmp);
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
	char	    *buff;
	static char *tail;
	int		    size[2];
	ssize_t      buff_bytes;
	char         *ret;
	int        buff_pos;
	int         buff_left;

	buff_left = BUFF_SIZE;
	buff = (char *)malloc(BUFF_SIZE);
	size[0] = 0;
	if (tail && tail[0] != '\0')
	{
		if ((ret = ft_str_split_end(&tail, &(*res), BUFF_SIZE)))
			return (ret);
	}
	else
		tail = (char *) ft_memalloc(sizeof(char)*(BUFF_SIZE + 1));
	buff_pos = 0;
	while (*res > 1)
	{
		if ((buff_bytes = read(fd, buff + buff_pos, buff_left)) > 0)
		{
			buff_pos += buff_bytes;
			buff_left -= buff_bytes;
			if (buff_left < (BUFF_SIZE / 2))
			{
				ret = ft_strdup(buff);
				ft_memdel((void **)&buff);
				buff = (char *)ft_memalloc(sizeof(char) * (BUFF_SIZE + buff_pos + buff_left));
				buff = ft_strcpy(buff, ret);
				ft_memdel((void **)&ret);
				buff_left += BUFF_SIZE;
			}
			if (ft_memchr(buff, '\n', buff_pos) || buff_bytes < BUFF_SIZE)
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
	//if (ret)
	//	free(ret);
	return (ret);
}

int	get_next_line(const int fd, char **line)
{
	int res;

	if (fd < 0 || fd > 10240 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	res = 2;
	if (line)
	{
		free(*line);
		*line = NULL;
	}
	*line = ft_get_buff(fd, &res);
	return (res);
}
