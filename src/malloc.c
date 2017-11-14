/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/13 17:38:25 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static t_data	*memory_maker(t_alloc *find, size_t size)
{
	t_data	*ptr;
	size_t	get_data;

	ptr = NULL;
	get_data = getpagesize();
	while ((size_t)(size + sizeof(t_data)) > get_data)
		get_data += getpagesize();
	ptr = mmap(NULL, get_data, PROT_READ |
		PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	ptr->block_size = get_data;
	ptr->user_size = size;
	ptr->next = NULL;
	ptr->user_data = ((void*)ptr) + sizeof(t_data);
	find->head->large_allocs++;
	find->head->total_allocs++;
	return (ptr);
}

static t_data	*allocate_big_node(t_alloc *find, size_t size)
{
	find->inside = find->head->large;
	if (!find->head->large)
		return ((find->head->large = memory_maker(find, size)));
	while (find->inside->next)
		find->inside = find->inside->next;
	return ((find->inside->next = memory_maker(find, size)));
}

static t_data	*use_smaller_node(t_alloc *find, t_data *start, size_t size)
{
	while (start)
	{
		if (start->available == 1)
		{
			start->user_size = size;
			start->available = 0;
			find->head->total_allocs++;
			break ;
		}
		start = start->next;
	}
	return (start);
}

static t_data	*allocate_smaller_node(t_alloc *find, size_t size)
{
	while (find->top)
	{
		if (size < TNYSIZE && find->top->tny_allocs < NODECOUNT)
		{
			find->top->tny_allocs++;
			return (use_smaller_node(find, find->top->tny, size));
		}
		else if (size >= TNYSIZE && find->top->med_allocs < NODECOUNT)
		{
			find->top->med_allocs++;
			return (use_smaller_node(find, find->top->med, size));
		}
		else if (!find->top->next)
			find->top->next = slab_carver();
		find->top = find->top->next;
	}
	return (NULL);
}

void			*malloc(size_t size)
{
	t_alloc find;
	void	*ptr;

	find.inside = NULL;
	find.head = get_head();
	find.top = find.head;
	if (size <= 0)
		return (NULL);
	if (size > MEDSIZE)
	{
		ptr = (allocate_big_node(&find, size))->user_data;
		return (ptr);
	}
	else
	{
		ptr = (allocate_smaller_node(&find, size))->user_data;
		return (ptr);
	}
	return (NULL);
}
