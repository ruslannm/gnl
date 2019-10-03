/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/10/03 18:00:55 by rgero            ###   ########.fr       */
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

int	ft_get_line(int fd, char **res)
{
	char	    *buff_ret;
	static char *tail;
	int         ret;

	buff_ret = (char *)malloc(BUFF_SIZE);
	buff_ret = NULL;
	if (tail && tail[0] != '\0')
	{
		if ((ret = ft_str_split_end(&res, BUFF_SIZE)))
			return (ret);
	}
	else
		tail = (char *) ft_memalloc(sizeof(char)*(BUFF_SIZE + 1));
	if ((ret = ft_get_buff(fd, &buff_ret) > 0))
		ret = ft_str_split_end(&tail, &buff_ret, BUFF_SIZE));
	ret = ft_str_split_end(&tail, &buff_ret, buff_bytes);
	ft_memdel((void **) &buff_ret);
	return (ret);
}

char	*ft_get_buff(int fd, int *res)
{
	char	    *buff;
	char        *tmp;
	ssize_t      buff_bytes;
	int         buff_pos;

	buff = (char *)malloc(BUFF_SIZE);
	buff_pos = 0;
	while ((buff_bytes = read(fd, buff + buff_pos, BUFF_SIZE)) > 0)
	{
		buff_pos += buff_bytes;
		if (ft_memchr(buff, '\n', buff_pos) || buff_bytes < BUFF_SIZE)
			break;
		tmp = ft_strdup(buff);
		ft_memdel((void **) &buff);
		buff = ft_strcpy(buff, tmp);
		ft_memdel((void **) &tmp);
	}
	if (buff_bytes > 1)
		*res = 1;
	else
		*res= (int)(buff_bytes));
	return (buff);
}


int	get_next_line(const int fd, char **line)
{
	char	    *buff_ret;
	static char *tail;
	int         ret;

	if (fd < 0 || fd > 10240 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	buff_ret = (char *)malloc(BUFF_SIZE);
	buff_ret = NULL;
	if (tail && tail[0] != '\0')
	{
		if ((ret = ft_str_split_end(&tail, BUFF_SIZE)))
			return (ret);
	}
	else
		tail = (char *) ft_memalloc(sizeof(char)*(BUFF_SIZE + 1));
	if ((ret = ft_get_buff(fd, &buff_ret) > 0))
		ret = ft_str_split_end(&tail, &buff_ret, BUFF_SIZE));
	ret = ft_str_split_end(&tail, &buff_ret, buff_bytes);
	ft_memdel((void **) &buff_ret);
	return (res);
}