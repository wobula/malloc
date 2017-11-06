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
	void *ptr;
	void *ptr2;
	int x;

	x = -1;
	while (++x < 999)
	{
		ptr = malloc(50);
		ptr2 = malloc(200);
		if (!ptr || !ptr2)
			break;
		ft_printf("med malloc : %p\n", ptr);
		ft_printf("tny malloc : %p\n", ptr2);
		ft_printf("%d\n\n", x);
	}
	return (0);
}
