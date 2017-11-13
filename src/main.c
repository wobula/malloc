/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/08 21:23:08 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		main(void)
{
	char *ptr;
	char *ptr2;
	char *ptr3;

	while (1)
	{
		ptr = malloc(-10);
		ptr2 = malloc(600);
		ptr3 = malloc(300);
		ptr3 = realloc(ptr3, 10);
		free(ptr);
		ptr = calloc(10, 500);
		free(ptr);
		free(ptr2);
		free(ptr3);
	}
	return (0);
}
