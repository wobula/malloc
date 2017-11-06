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
#include <sys/resource.h>

#define tnysize 100
#define medsize 500

t_node	*head = NULL;

t_data	*allocate_data(t_data *start, int capacity, size_t node_count, int storage_size)
{
	t_data *tmp;

	tmp = start;
	while (node_count > 0)
	{
		tmp->data = (void*)(tmp + 1);
		tmp->next = (t_data*)((char*)tmp->data + storage_size);
		node_count--;
		capacity -= (sizeof(t_data) + storage_size);
		ft_printf("tny data    : %p\n", tmp->data);
		ft_printf("tmp->next   : %p\n", tmp->next);
		ft_printf("tny capacity: %d\n", capacity);
		ft_printf("tny node cot: %d\n", node_count);
		tmp = tmp->next;
	}
	return (start);	
}

t_node	*get_head()
{
	int get_size;
	int data;

	if (!head)
	{
		get_size = sizeof(t_node) + ((tnysize + sizeof(t_data)) * 100);
		data = 0;
		while (data < get_size)
			data = data + getpagesize();
		head = mmap(NULL, data, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		head->available = data - (sizeof(t_node) + sizeof(t_data));
		head->tny = (t_data*)(head + 1);
		head->tny_size = (sizeof(t_data) + tnysize) * 100;
		head->tny = allocate_data(head->tny, head->tny_size, 100, tnysize);
	}
	return(head);
}

void	 *malloc(size_t size)
{
	t_node *ptr;
	
	ft_putnbr(size);
	ptr = get_head();
	return (ptr);
}

int		main(void)
{
	t_node *head;

	head = (t_node*)malloc(50);
	ft_printf("head node: %p\n", head);
	ft_printf("available: %d\n", head->available);
	ft_printf("tny node : %p\n", head->tny);
	return (0);
}
