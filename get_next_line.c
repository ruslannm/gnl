/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/10/06 10:32:19 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_str_realloc(char **str, int new_len)
{
	char	*tmp;
	int		res;
	char	*p;

	p = *str;
	tmp = ft_strdup(*str);
	if (!(*str = (char *)ft_memalloc(sizeof(char) * (new_len + 1))))
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

int		ft_str_split_end(char **tail, char **line, int get_buff, int res)
{
	int		seek;
	int		l;
	char	*chr;
	char	*tmp;

	if (!(*tail))
		return (0);
	if (!(tmp = ft_strdup(*tail)))
		return (-1);
	ft_memdel((void **)&(*tail));
	l = ft_strlen(tmp);
	if ((chr = ft_memchr(tmp, '\n', l)) || (l > 0 && get_buff < BUFF_SIZE))
	{
		res = 1;
		seek = (chr != NULL ? chr - tmp : l);
		if (!(*line = ft_strsub(tmp, 0, seek)))
			res = -1;
		if ((l - seek) > 1)
			if (!(*tail = ft_strsub(tmp, seek + 1, l - seek - 1)))
				res = -1;
	}
	else if (!(*tail = ft_strdup(tmp)))
		res = -1;
	ft_memdel((void **)&tmp);
	return (res);
}

int		ft_get_buff(int fd, char **buff)
{
	ssize_t	buff_bytes;
	int		buff_pos;
	int		res;

	if (!(*buff = (char *)malloc(BUFF_SIZE + 1)))
		return (-1);
	buff_pos = 0;
	while ((buff_bytes = read(fd, *buff + buff_pos, BUFF_SIZE)) > 0)
	{
		buff_pos += buff_bytes;
		if (ft_memchr(buff, '\n', buff_pos) || buff_bytes < BUFF_SIZE)
			break ;
		if ((res = ft_str_realloc(&(*buff), buff_pos + 1)) == -1)
			break ;
	}
	if (res == -1)
		ft_memdel((void **)&(*buff));
	else
	{
		(*buff)[buff_pos] = '\0';
		res = (int)(buff_bytes);
	}
	return (res);
}

int		get_next_line(const int fd, char **line)
{
	char		*buff_ret;
	static char	*tail;
	int			ret;
	char		*tmp;

	ret = 0;
	tmp = NULL;
	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (-1);
	if ((ret = ft_str_split_end(&tail, &(*line), BUFF_SIZE, 0)))
		return (ret);
	if (tail)
		if (!(tmp = ft_strdup(tail)))
			return (-1);
	ft_memdel((void **)&tail);
	ret = ft_get_buff(fd, &buff_ret);
	if (tmp == NULL && buff_ret)
		tail = ft_strdup(buff_ret);
	else if (buff_ret)
		tail = ft_strjoin(tmp, buff_ret);
	ft_memdel((void **)&tmp);
	if (ret != -1)
		ret = ft_str_split_end(&tail, &(*line), ret, 0);
	ft_memdel((void **)&buff_ret);
	return (ret);
}
