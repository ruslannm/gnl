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

static int		ft_lst_pop(t_list **root, char **line, int fd, int ret)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *root;
	prev = NULL;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
		{
			if (!(*line = ft_strdup((char *)tmp->content)))
				ret = -1;
			if (prev)
				prev->next = tmp->next;
			else
				*root = tmp->next;
			free(tmp->content);
			free(tmp);
			return(ret) ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	if (!(*line = ft_strnew(1)))
		ret = -1;
	return (ret);
}

static int	ft_lst_push(t_list **root, int fd, char *tail)
{
	t_list			*tmp;

	if (!*root)
	{
		if (!(*root = ft_lstnew(tail, ft_strlen(tail) + 1)))
			return (-1);
		(*root)->content_size = fd;
	}
	else
	{
		tmp = *root;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = ft_lstnew(tail, ft_strlen(tail) + 1)))
			return (-1);
		tmp->next->content_size = fd;
	}
	return (1);
}

int			ft_get_buff(int fd, char **line, char **tail)
{
	ssize_t	buff_bytes;
	char	*buff_pos;
	char	*tmp;
	char	buff[BUFF_SIZE + 1];

	if (!(*line))
		return (-1);
	while ((buff_bytes = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[buff_bytes] = '\0';
		if (!(tmp = ft_strjoin(*line, buff)))
			return (-1);
		free(*line);
		*line = tmp;
		if ((buff_pos = ft_strchr(*line, '\n')))
		{
			if (!(*tail = ft_strdup(buff_pos + 1)))
				return (-1);
			*buff_pos = '\0';
			return (1);
		}
	}
	if (ft_strlen(*line) > 0)
		return (1);
	return (buff_bytes < 0 ? -1 : 0);
}

int			get_next_line(const int fd, char **line)
{
	char			*tail;
	int				ret;
	static t_list	*root = NULL;
	char			*buff_pos;

	tail = NULL;
	ret = 1;
	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (-1);
	if (ft_lst_pop(&root, &(*line), fd, 1) == -1)
		return (-1);
	if ((buff_pos = ft_strchr(*line, '\n')))
	{
		if (!(tail = ft_strdup(buff_pos + 1)))
			ret = -1;
		*buff_pos = '\0';
	}
	else
		ret = ft_get_buff(fd, &(*line), &tail);
	if (tail && tail[0] != '\0')
		ret = ft_lst_push(&root, fd, tail);
	ft_memdel((void **)&tail);
	return (ret);
}
