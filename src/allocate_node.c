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

t_node	*g_head = NULL;

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

t_node	*expand_head(void)
{
	int		get_size;
	int		data;
	t_node	*ptr;

	get_size = sizeof(t_node) +
					((TNYSIZE + sizeof(t_data)) * 100) +
					((MEDSIZE + sizeof(t_data)) * 100);
	data = 0;
	while (data < get_size)
		data = data + getpagesize();
	ptr = mmap(NULL, data, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	ptr->tny_allocations = 100;
	ptr->tny = (t_data*)(ptr + 1);
	ptr->tny_size = (sizeof(t_data) + TNYSIZE) * 100;
	ptr->tny_end = allocate_data(ptr->tny, 100, TNYSIZE);
	ptr->med_allocations = 100;
	ptr->med = (t_data*)(((char*)(ptr->tny_end + 1)) + TNYSIZE);
	ptr->med_size = (sizeof(t_data) + MEDSIZE) * 100;
	ptr->med_end = allocate_data(ptr->med, 100, MEDSIZE);
	ptr->large = NULL;
	ptr->next = NULL;
	return (ptr);
}

t_node	*get_head(void)
{
	if (!g_head)
		g_head = expand_head();
	return (g_head);
}
