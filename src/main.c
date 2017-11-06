/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/06 09:02:25 by rschramm         ###   ########.fr       */
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
	t_node *ptr;
	t_node *tmp;

	ptr = (t_node*)mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp = ptr;
	while (ptr)
	{
		tmp->next = add_node(tmp);
		ft_printf("%p\n", tmp);
		tmp = tmp->next;
	}
	return (0);
}
