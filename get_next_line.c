/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/09/23 19:25:40 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libft.h>

int	get_next_line(const int fd, char **line)
{
	size_t buff_bytes;
	size_t seek;
	char buff[BUFF_SIZE];
	static char *tmp_line;
	char *tmp;

	if (tmp_line == 0)
	{
		while ((buff_bytes = read(fd, buff, BUFF_SIZE)))
		{
			buff[buff_bytes] = '\0';
			seek = 0;
			while (seek < buff_bytes || buff[seek] != '\n')
				seek++;
			tmp = (char *) malloc(sizeof(char) * (seek + 1));
			ft_strncpy(tmp, buff, seek + 1);
			tmp[seek - 1] = '\n';
			tmp[seek] = '\0';
		}
		*line = tmp;
	}
	return (1);
}