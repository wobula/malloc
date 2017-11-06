/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/06 09:16:41 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_node *add_node(t_node *start)
{
	t_node *tmp;

	tmp = start + sizeof(t_node);
	tmp->size = start->size + 10;
	tmp->count = start->count + 1;
	return (tmp);
}

int	main(void)
{
	char *ptr;
	int size;
	int x;

	x = -1;
	size = getpagesize();
	ptr = (char*)mmap(NULL, size * 5, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	while (1)
	{
		x++;
		ptr[x] = 'a';
		ft_printf("%d\n", x);
	}
	return (0);
}
