/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:31:45 by rgero             #+#    #+#             */
/*   Updated: 2019/09/23 19:01:20 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	get_next_line(const int fd, char **line)
{
	size_t  buff_bytes;
	size_t  seek;
	char buff[BUFF_SIZE];

	*line = NULL;
	if (buff == 0)
	{
		while (buff_bytes = read(fd, buff, BUFF_SIZE))
		{
			buff[buff_bytes] = '\0';
			seek = 0;
			while (seek < buff_bytes || buff[seek] != '\n')
				seek++;
			if (seek < buff_bytes)

					break;
			}
			else
			{
				while (buf[seek] != '\n')
				{
					write(1, &(buf[i]), 1);
					seek++;
				}
				write(1, "\n", 1);
			}




		}

