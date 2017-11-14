/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/14 14:55:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_node	*g_head = NULL;

static void		block_builder(t_data *start, int node_count, int storage_size)
{
	ft_putstr("Inside block builder\n");
	while (node_count-- != 0)
	{
		start->user_data = (void*)(start + 1);
		start->available = 1;
		ft_dprintf(2, "Allocate: %p for %zu\n", start->user_data,
				storage_size);
		if (node_count != 0)
		{
			start->next = (t_data*)((char*)start->user_data + storage_size);
			start = start->next;
		}
	}
	start->next = NULL;
}

static t_node	*node_builder(void)
{
	t_node *this;
	int		get_size;
	int		data;

	get_size = sizeof(t_node) + ((TNYSIZE + sizeof(t_data)) * NODECOUNT) +
					((MEDSIZE + sizeof(t_data)) * NODECOUNT);
	data = 0;
	while (data < get_size)
		data = data + getpagesize();
	this = mmap(NULL, data, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	this->large = NULL;
	this->next = NULL;
	this->freed_bytes = 0;
	this->tny_allocs = 0;
	this->med_allocs = 0;
	this->large_allocs = 0;
	this->frees = 0;
	this->freed_bytes = 0;
	this->total_allocs = 0;
	this->slab_size = data;
	return (this);
}

t_node			*slab_carver(void)
{
	t_node	*ptr;

	ptr = node_builder();
	ptr->tny = (t_data*)(ptr + 1);
	ptr->tny_end = (t_data*)(((char*)(ptr->tny + 1)) +
			((sizeof(t_data) + TNYSIZE) * (NODECOUNT)));
	ft_dprintf(2, "Allocate: tny beg %p\n", ptr->tny);
	ft_dprintf(2, "Allocate: tny end %p\n", ptr->tny_end);
	ptr->tny_block = (sizeof(t_data) + TNYSIZE) * NODECOUNT;
	block_builder(ptr->tny, NODECOUNT, TNYSIZE);
	ptr->med = (t_data*)(((char*)(ptr + 1)) +
			((sizeof(t_data) + TNYSIZE) * (NODECOUNT)));
	ft_dprintf(2, "Allocate: med beg %p\n", ptr->med);
	ptr->med_block = (sizeof(t_data) + MEDSIZE) * NODECOUNT;
	ptr->med_end = (t_data*)(((char*)(ptr->med + 1)) +
			((sizeof(t_data) + MEDSIZE) * (NODECOUNT)));
	ft_dprintf(2, "Allocate: med end %p\n", ptr->med_end);
	block_builder(ptr->med, NODECOUNT, MEDSIZE);
	return (ptr);
}

void		free_head(void)
{
	t_node *please;
	t_node *prev;

	please = g_head;
	while (please)
	{
		prev = please;
		please = please->next;
		munmap(prev, prev->slab_size);
		prev = NULL;
	}
	if (prev)
		munmap(prev, prev->slab_size);
	g_head = NULL;
}

t_node		*get_head(void)
{
	if (!g_head)
		g_head = slab_carver();
	return (g_head);
}
