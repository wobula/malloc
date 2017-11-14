/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/13 17:55:08 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <stdio.h>

int		main(void)
{
	char	**ptr;
	int		x;

	while (1)
	{
		ptr = (char**)calloc(sizeof(void *), 200);
		x = -1;
		while (x++ < 200)
		{
			ptr[x] = (char*)malloc(10);
			ptr[x][0] = 'a';
			ft_dprintf(2, "Malloc char: %c\n", ptr[x][0]);
			ptr[x] = (char*)realloc(ptr[x], 300);
			ptr[x][0] = 'b';
			ft_dprintf(2, "Malloc char: %c\n", ptr[x][0]);
			free(ptr[x]);
		}
		free(ptr);
	}
	return (0);
}
