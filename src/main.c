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
	//while (1)
	//{
		x = -1;
	while (x++ < 2)
	{
		ft_putstr("sup\n");
		ptr = malloc(10);
		ptr2 = malloc(10);
		ptr3 = malloc(301);
		ptr4 = malloc(301);
		ft_putstr("yo\n");
		free(ptr);
		ft_putstr("yo1\n");
		free(ptr2);
		ft_putstr("yo2\n");
		free(ptr3);
		ft_putstr("yo3\n");
		free(ptr4);
		ft_putstr("yo4\n");
	}
//}
	return (0);
}
