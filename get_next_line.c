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

#include <zlib.h>
#include "get_next_line.h"


static char		*ft_lst_pop(t_list **root, int fd)
{
	t_list	*tmp;
	t_list	*prev;
	char 	*ret;

	if (!*root)
		return (NULL);
	tmp = *root;
	prev = NULL;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
		{
			ret = ft_strdup((char *)tmp->content);
			if (prev)
				prev->next = tmp->next;
			ret = ft_strdup((char *)(*root)->content);
			free((*root)->content);
			free(*root);
			*root = NULL;
			return (ret);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

static int	ft_lst_push(t_list **root, int fd, char *tail)
{
	//static t_list	*root;
	t_list			*tmp;
	t_list			*prev;

	if (!*root && tail && tail[0] != 0)
	{
		*root = ft_lstnew(tail, ft_strlen(tail));
		(*root)->content_size = fd;
	}
	else
	{
		tmp = *root;
		while (tmp->next)
			tmp = tmp->next;
		if (tail && tail[0] != '\0')
		{
			tmp->next = ft_lstnew(tail, ft_strlen(tail));
			(tmp)->content_size = fd;
		}
	}
	return (1);
}


int		ft_get_buff(int fd, char **line, char **tail)
{
	ssize_t	buff_bytes;
	char		*buff_pos;
	int		res;
	char *tmp;
	char buff[BUFF_SIZE + 1];

	buff_pos = 0;
	while ((buff_bytes = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[buff_bytes] = '\0';
		tmp = ft_strjoin(*line, buff);
		if ((buff_pos = ft_strchr(tmp, '\n')))
			break;
		free(*line);
		*line = ft_strdup(tmp);
		free(tmp);
	}
	if (buff_pos > 0)
	{
		*tail = ft_strdup(buff_pos + 1);
		free(*line);
		*buff_pos = '\0';
		*line = ft_strdup(tmp);
		free(tmp);
		return (1);
	}
	else if (ft_strlen(*line) > 0)
		return (1);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	char			*tail;
	int				ret;
	static t_list	*root;

	ret = 0;
	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (-1);
	if (!(*line = ft_lst_pop(&root, fd)))
		*line = ft_strnew(1);
	ret = ft_get_buff(fd, &(*line), &tail);
	if (tail)
		ft_lst_push(&root, fd, tail);
	ft_memdel((void **)&tail);
	return (ret);
}
