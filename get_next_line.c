/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/10/05 11:17:01 by rgero            ###   ########.fr       */
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

	res = (get_buff == 0 ? 0 : 1);
	tmp = ft_strdup(*tail);
	ft_memdel((void **)&(*tail));
	len = ft_strlen(tmp);
	if ((seekchr = ft_memchr(tmp, '\n', len)) || (len > 0 && get_buff < BUFF_SIZE))
	{
		seek = (seekchr != NULL ? seekchr - tmp : len);
		*line = ft_strsub(tmp, 0, seek);
		if ((len - seek) > 1)
			*tail = ft_strsub(tmp, seek + 1, len - seek - 1);
		res = 1;
	}
	else if (get_buff < BUFF_SIZE)
		res = ((*line = ft_strdup(tmp)) ? res: -1);
	ft_memdel((void **)&tmp);
	return (res);
}

char	*ft_get_buff(int fd, int *res)
{
	char	    *buff;
	ssize_t      buff_bytes;
	int         buff_pos;

	buff = (char *)malloc(BUFF_SIZE + 1);
	//buff = NULL;
	buff_pos = 0;
	while ((buff_bytes = read(fd, buff + buff_pos, BUFF_SIZE)) > 0)
	{
		buff_pos += buff_bytes;
		if (ft_memchr(buff, '\n', buff_pos) || buff_bytes < BUFF_SIZE)
			break;
		if ((*res = ft_str_realloc(&buff, buff_pos + 1)) == -1)
			break;
	}
	*res= (int)(buff_bytes);
	buff[buff_pos] = '\0';
	return (buff);
}

int	get_next_line(const int fd, char **line)
{
	char	    *buff_ret;
	static char *tail;
	int         ret;
	char        *tmp;

	ret = 0;
	tmp = NULL;
	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (-1);
	if (tail)
	{
		if ((ret = ft_str_split_end(&tail, &(*line), BUFF_SIZE)))
			return (ret);
		if (!(tmp = ft_strdup(tail)))
			return (-1);
		ft_memdel((void **) &tail);
	}
	buff_ret = ft_get_buff(fd, &ret);
	if (tmp == NULL)
		tail = ft_strdup(buff_ret);
	else
		tail = ft_strjoin(tmp, buff_ret);
	ft_memdel((void **) &tmp);
	ret = ft_str_split_end(&tail, &(*line), ret);
	ft_memdel((void **) &buff_ret);
	return (ret);
}