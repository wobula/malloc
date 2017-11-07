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
	t_node *ptr;
	char 	*ptr2;
	int x;

	ptr = (t_node*)malloc(50);
	free((void*)ptr);
	ptr2 = (char*)malloc(101);
	x = -1;
	while (++x < 101)
		ptr2[x] = 'A';
	ft_printf("%s\n", ptr2);
	free(ptr2);
	return (0);
}
