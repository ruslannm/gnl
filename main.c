/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:36:53 by rgero             #+#    #+#             */
/*   Updated: 2019/09/29 11:40:56 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	ft_read(int fd)
{
	char	*str;
	int i;

	while ((i = get_next_line(fd, &str)))
	{
		ft_putstr(str);
		ft_putstr("-");
		ft_putnbr(i);
		ft_putstr("-");
	}
	ft_putstr(str);
	ft_putstr("-");
	ft_putnbr(i);
	ft_putstr("-");

	if (fd > 1)
		close(fd);
}


int main(int argc, char **argv)
{
	char *s;
	int i;
	int		fd;
	char		*line;

	printf("Hello, World!\n");
	ft_putstr("test_str\n");



	if (argc == 2)
	{
		i = 0;
		fd = open(argv[1], O_RDONLY);
		ft_read(fd);
		/*
		while ((get_next_line(fd, &line)) == 1)
		{
			ft_putstr(line);
			ft_putchar('\n');
		}
		*/
		//close(fd);
	}
	return (0);

}