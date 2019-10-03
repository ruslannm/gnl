/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/10/03 19:45:50 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_str_realloc(char **str, int new_len)
{
	char *tmp;
	int res;
	char *p;


	p = *str;
	tmp =  ft_strdup(*str);
	if (!(*str = (char *) ft_memalloc(sizeof(char)*(new_len + 1))))
	{
		res = -1;
	}
	else
	{
		*str = p;
		*str = ft_strcpy(*str, tmp);
		res = 1;
	}
	ft_memdel((void **)&tmp);
	return (res);
}

int   ft_str_split_end(char **tail, char **line, int get_buff)
{
	int seek;
	int len;
	char *seekchr;
	char *tmp;
	int res;

	res = 0;
	len = ft_strlen(*tail);
	if ((seekchr = ft_memchr(*tail, '\n', len)))
	{
		seek = seekchr - *tail;
		*line = ft_strsub(*tail, 0, seek);
		if ((len - seek) == 1)
			ft_memdel((void **)&(*tail));
		else
		{
			tmp = ft_strsub(*tail, seek + 1, len - seek - 1);
			ft_memdel((void **)&(*tail));
			*tail = ft_strdup(tmp);
			ft_memdel((void **)&tmp);
		}
		res = 1;
	}
	else if (get_buff == 0)
	{
		*line = ft_strdup(*tail);
		ft_memdel((void **)&(*tail));
		res = 1;
	}
	else if (get_buff == -1)
		res = get_buff;
	return (res);
}

char	*ft_get_buff(int fd, int *res)
{
	char	    *buff;
	char        *tmp;
	ssize_t      buff_bytes;
	int         buff_pos;

	buff = (char *)malloc(BUFF_SIZE);
	//buff = NULL;
	buff_pos = 0;
	while ((buff_bytes = read(fd, buff + buff_pos, BUFF_SIZE)) > 0)
	{
		buff_pos += buff_bytes;
		if (ft_memchr(buff, '\n', buff_pos) || buff_bytes < BUFF_SIZE)
			break;
		if ((*res = ft_str_realloc(&buff, buff_pos)) == -1)
			break;
	}
	if (buff_bytes > 1)
		*res = 1;
	else
		*res= (int)(buff_bytes);
	return (buff);
}

int	get_next_line(const int fd, char **line)
{
	char	    *buff_ret;
	static char *tail;
	int         ret;

	ret = 0;
	if (fd < 0 || fd > 10240 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	if (tail && tail[0] != '\0')
	{
		if ((ret = ft_str_split_end(&tail, &(*line), BUFF_SIZE)))
			return (ret);
	}
	else
		tail = (char *) ft_memalloc(sizeof(char)*(BUFF_SIZE + 1));
	buff_ret = ft_get_buff(fd, &ret);
	if ((ret = ft_str_realloc(&tail, ft_strlen(tail) + ft_strlen(buff_ret) + 1))  > 0)
	{
		tail = strcat(tail, buff_ret);
		ret = ft_str_split_end(&tail, &(*line), BUFF_SIZE);
	}
	ft_memdel((void **) &buff_ret);
	return (ret);
}