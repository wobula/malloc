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
	int x;

	x = -1;
	while (1)
	{
	while (x++ < 2)
	{
		ptr = malloc(10);
		ptr2 = malloc(10);
		ptr3 = malloc(10);
		ptr4 = malloc(10);
		free(ptr);
		free (ptr2);
		free(ptr3);
		free(ptr4);
	}
}
	return (0);
}
