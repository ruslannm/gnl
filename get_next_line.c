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

static void	ft_del(void *content, size_t len)
{
	len = 0;
	free(content);
}

static char		*ft_lst_pop(t_list *root, int fd)
{
	t_list	*tmp;
	t_list	*prev;
	char 	*ret;

	if (!root)
		return (NULL);
	tmp = root;
	prev = NULL;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
		{
			ret = (char *)tmp->content;
			if (prev)
				prev->next = tmp->next;
			ft_lstdelone(&tmp, &ft_del);
			return (ret);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

static t_list		*ft_lst_push(int fd, char *tail)
{
	static t_list	*root;
	t_list			*tmp;
	t_list			*prev;

	if (!root && tail && tail[0] != 0)
	{
		root = ft_lstnew(tail, ft_strlen(tail));
		root->content_size = fd;
	}
	else if (!root)
		return (NULL);
	else
	{
		tmp = root;
		while (tmp->next)
		{
			if (tmp->content_size == fd)
				return (root);
			tmp = tmp->next;
		}
		if (tail && tail[0] != '\0')
			tmp->next = ft_lstnew(tail, ft_strlen(tail));
	}
	return (root);
}

int		ft_str_realloc(char **str, int new_len)
{
	char	*tmp;
	int		res;
	char	*p;

	p = *str;
	tmp = ft_strdup(*str);
	if (!(*str = (char *)ft_memalloc(sizeof(char) * (new_len + 1))))
		res = -1;
	else
	{
		*str = p;
		*str = ft_strcpy(*str, tmp);
		res = 1;
	}
	ft_memdel((void **)&tmp);
	return (res);
}

int		ft_str_split_end(t_list **list, char **line, int get_buff, int fd)
{
	int		seek;
	int		l;
	char	*chr;
	char	*tail;
	int		res;

	res = 0;
	if (!(*list = ft_lst_push(fd, *line)))
		return (0);
	tail = ft_lst_pop(*list, fd);
	l = ft_strlen(tail);
	if ((chr = ft_strchr(tail, '\n')) || (l > 0 && get_buff < BUFF_SIZE))
	{
		res = 1;
		seek = (chr != NULL ? chr - tail : l);
		if (!(*line = ft_strsub(tail, 0, seek)))
			res = -1;
		if (*line && (l - seek) > 1)
			*list = ft_lst_push(fd, chr + 1);
	}
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
		if (ft_memchr(*buff, '\n', buff_pos) || buff_bytes < BUFF_SIZE)
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
	char	*buff_ret;
	//char	*tail;
	t_list	*list;
	int		ret;
	char	*tmp;

	ret = 0;
	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (-1);
	if ((ret = ft_str_split_end(&list, &(*line), BUFF_SIZE, fd)))
		return (ret);
	ret = ft_get_buff(fd, &buff_ret);
	if (buff_ret)
	{
		if (!list)
			tmp = ft_strnew(0);
		else
			tmp = ft_strdup(list->content);
		*line = ft_strjoin(tmp, buff_ret);
		ft_memdel((void **)&tmp);
	}
	if (ret != -1)
		ret = ft_str_split_end(&list, &(*line), ret, fd);
	//ft_memdel((void **)&tail);
	ft_memdel((void **)&buff_ret);
	return (ret);
}
