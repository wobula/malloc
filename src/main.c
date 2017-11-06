/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/06 10:42:48 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <sys/resource.h>

t_node	*add_node(t_node *this)
{
	t_node *ptr;

	ptr = this + sizeof(t_node*);
	ptr->size = this->size - sizeof(t_node*);
	ptr->count = this->count + 1;
	ptr->next = NULL;
	return (ptr);
}

int	main(void)
{
	t_node *ptr;
	t_node *tmp;
	int size;
	int x;

	x = -1;
	size = getpagesize();
	ptr = (t_node*)mmap(NULL, size * 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	ptr->size = size - sizeof(t_node*);
	ptr->next = NULL;
	ptr->count = 1;
	tmp = ptr;
	while (tmp->size > 0)
	{
		tmp->next = add_node(tmp);
		ft_printf("leftover space: %d\n", tmp->next->size);
		ft_printf("node address: %p\n", tmp->next);
		ft_printf("node count: %d\n", tmp->next->count);
		tmp = tmp->next;
	}
	return (0);
}
