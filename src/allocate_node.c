/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/06 14:06:23 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_node	*head = NULL;

t_data	*allocate_data(t_data *start, int capacity, size_t node_count, int storage_size)
{
	t_data *tmp;
	size_t id;

	tmp = start;
	id = 0;
	while (node_count > 0)
	{
		tmp->data = (void*)(tmp + 1);
		tmp->next = (t_data*)((char*)tmp->data + storage_size);
		tmp->available = 1;
		tmp->id += 1;
		node_count--;
		capacity -= (sizeof(t_data) + storage_size);
		ft_printf("tny data    : %p\n", tmp->data);
		ft_printf("tmp->next   : %p\n", tmp->next);
		ft_printf("tny capacity: %d\n", capacity);
		ft_printf("tny node cot: %d\n", node_count);
		tmp = tmp->next;
	}
	tmp->next = NULL;
	return (tmp);	
}

t_node	*get_head()
{
	int get_size;
	int data;

	if (!head)
	{
		ft_putstr("allocating head node\n");
		get_size = sizeof(t_node) +
					((tnysize + sizeof(t_data)) * 100) +
					((medsize + sizeof(t_data)) * 100);
		data = 0;
		while (data < get_size)
			data = data + getpagesize();
		head = mmap(NULL, data, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		head->tny = (t_data*)(head + 1);
		head->tny_size = (sizeof(t_data) + tnysize) * 100;
		head->tny_end = allocate_data(head->tny, head->tny_size, 100, tnysize);
		head->tny->id = 0;
		head->med = (t_data*)(((char*)(head->tny_end + 1)) + tnysize);
		head->med_size = (sizeof(t_data) + medsize) * 100;
		head->med_end = allocate_data(head->med, head->med_size, 100, medsize);
		head->med->id = 0;
		ft_printf("med start: %p\n", head->med);
	}
	return(head);
}