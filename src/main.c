/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/06 14:06:23 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		main(void)
{
	char	*ptr;
	int		x;

	ptr = malloc(10);
	x = -1;
	while (++x < 9)
		ptr[x] = 'a';
	ptr[x] = '\0';
	ft_printf("1st: %s\n\n", ptr);
	ptr = realloc(ptr, 1000);
	ft_printf("2nd: %s\n\n", ptr);
	x = 8;
	while (++x < 999)
		ptr[x] = 'b';
	ptr[x] = '\0';
	ft_printf("2nd: %s\n\n", ptr);
	show_alloc_mem();
	free(ptr);
	return (0);
}
