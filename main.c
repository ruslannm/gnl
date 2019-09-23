/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:36:53 by rgero             #+#    #+#             */
/*   Updated: 2019/09/23 19:27:53 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"

int main()
{
	char *s;
	int i;

	printf("Hello, World!\n");
	ft_putstr("test_str\n");
	i = get_next_line(1, s);
	ft_putstr(s);

	return 0;
}