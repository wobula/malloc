/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/14 14:24:14 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <stdio.h>

int		main(void)
{
	char	**ptr;
	int		x;
	int		y;

	while (1)
	{
		ptr = (char**)calloc(sizeof(char *), 200);
		x = -1;
		y = 0;
		while (x++ < 200)
		{
			y = -1;
			ptr[x] = (char*)malloc(10);
			while (++y < 8)
				ptr[x][y] = 'a';
			ptr[x][y] = '\0';
			ft_dprintf(2, "Malloc string: %s\n", ptr[x]);
			ptr[x] = (char*)realloc(ptr[x], 300);
			y = -1;
			while (++y < 298)
				ptr[x][y] = 'b';
			ptr[x][y] = '\0';
			ft_dprintf(2, "realloc string: %s\n", ptr[x]);
		}
		x = -1;
		while (x++ < 200)
		{
			free(ptr[x]);
		}
		free(ptr);
	}
	return (0);
}
