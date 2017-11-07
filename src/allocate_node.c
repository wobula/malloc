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

t_data	*allocate_data(t_data *start, size_t node_count, int storage_size)
{
	t_data *tmp;

	tmp = start;
	while (node_count > 0)
	{
		tmp->data = (void*)(tmp + 1);
		tmp->next = (t_data*)((char*)tmp->data + storage_size);
		tmp->available = 1;
		node_count--;
		tmp = tmp->next;
	}
	tmp->next = NULL;
	return (tmp);	
}

t_node *expand_head()
{
	int get_size;
	int data;
	t_node *ptr;

	get_size = sizeof(t_node) +
					((tnysize + sizeof(t_data)) * 100) +
					((medsize + sizeof(t_data)) * 100);
	data = 0;
	while (data < get_size) data = data + getpagesize();
	ptr = mmap(NULL, data, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	ptr->tny_allocations = 100;
	ptr->tny = (t_data*)(ptr + 1);
	ptr->tny_size = (sizeof(t_data) + tnysize) * 100;
	ptr->tny_end = allocate_data(ptr->tny, 100, tnysize);
	ptr->med_allocations = 100;
	ptr->med = (t_data*)(((char*)(ptr->tny_end + 1)) + tnysize);
	ptr->med_size = (sizeof(t_data) + medsize) * 100;
	ptr->med_end = allocate_data(ptr->med, 100, medsize);
	ptr->large = NULL;
	ptr->next = NULL;
	return (ptr);
}

t_node	*get_head()
{
	if (!head)
		head = expand_head();
	return(head);
}