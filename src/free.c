/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/06 14:06:23 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static int	check_big_nodes(t_alloc find, void *this)
{
	if (!find.head->large)
		return (0);
	if (find.head->large->user_data == this)
	{
		find.inside = find.head->large->next;
		find.head->freed_bytes += find.head->large->user_size;
		munmap(find.head->large, find.head->large->block_size);
		find.head->large = find.inside;
		return (1);
	}
	find.inside = find.head->large->next;
	find.prev = find.head->large;
	while (find.inside)
	{
		if (find.inside->user_data == this)
		{
			find.prev->next = find.inside->next;
			find.head->freed_bytes += find.inside->user_size;
			munmap(find.inside, find.inside->block_size);
			return (1);
		}
		find.prev = find.inside;
		find.inside = find.inside->next;
	}
	return (0);
}

static int	free_entire_slab(t_alloc find)
{
	if (find.top != find.head)
	{
		find.prev_node->next = find.top->next;
		munmap(find.top, find.top->slab_size);
	}
	return (1);
}

static int	get_specific_node(t_alloc find, t_data inside, void *this)
{
	while (find.inside)
	{
		if (find.inside->user_data == this)
		{
			if (find.inside->available == 0)
			{
				ft_dprintf(2, "Free: freeing %p\n", find.inside->user_data);
				find.inside->available = 1;
				find.head->freed_bytes += inside.user_size;
				if (find.top->med_allocs == 0 && find.top->tny_allocs == 0)
					return ((free_entire_slab(find)));
				return (1);
			}
			return (0);
		}
		find.inside = find.inside->next;
	}
	ft_dprintf(2, "Free: something is very wrong\n");
	return (0);
}

static int	check_smaller_nodes(t_alloc find, void *this)
{
	find.prev_node = NULL;
	while (find.top)
	{
		if (this < (void*)find.top->med)
		{
			find.inside = find.top->tny;
			find.top->tny_allocs--;
			return ((get_specific_node(find, *find.inside, this)));
		}
		else if (this < (void*)find.top->med_end)
		{
			find.inside = find.top->med;
			find.top->med_allocs--;
			return ((get_specific_node(find, *find.inside, this)));
		}
		find.prev_node = find.top;
		find.top = find.top->next;
	}
	return (0);
}

void		free(void *this)
{
	t_alloc find;

	find.head = get_head();
	find.top = find.head;
	if (!this)
		return ;
	if (check_smaller_nodes(find, this))
		find.head->frees++;
	else if (check_big_nodes(find, this))
		find.head->frees++;
	else
		ft_dprintf(2, "Free: Pointer was not allocated\n");
}
