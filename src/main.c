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
int		main(void)
{
	char *ptr;
	char *ptr2;
	char *ptr3;
	char *ptr4;
	char *ptr5;
	char *ptr6;
	char *ptr7;
	char *ptr8;
	char *ptr9;
	int	x;

	x = 0;
	while (1)
	{
		ptr = malloc(10);
		ptr[x] = 'a';
		ptr2 = malloc(300);
		ptr2[x] = 'b';
		ptr3 = malloc(50000);
		ptr3[x] = 'f';
		ptr3 = realloc(ptr3, 10);
		ptr3[0] = 'a';
		ptr4 = malloc(50000);
		ptr4[0] = 'a';
		ptr5 = calloc(10, 500);
		ptr5[0] = 'z';
		ptr6 = malloc(5000);
		ptr6[0] = 'a';
		ptr7 = malloc(305);
		ptr7[0] = 'f';
		ptr8 = malloc(50);
		ptr8[0] = 'h';
		ptr9 = malloc(400);
		ptr9[0] = 'v';

		free(ptr);
		free(ptr2);
		free(ptr3);
		free(ptr4);
		free(ptr5);
		free(ptr6);
		free(ptr7);
		free(ptr8);
		free(ptr9);
	}
	return (0);
}
