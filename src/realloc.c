/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/06 14:06:23 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static int	get_specific_allocation(t_alloc *find, t_data *inside, void *this)
{
	while (inside)
	{
		if (inside->user_data == this)
		{
			ft_dprintf(2, "Realloc: smaller section %p\n", inside->user_data);
			find->inside = inside;
			return (1);
		}
		inside = inside->next;
	}
	return (0);
}

static int	search_small_nodes(t_alloc *find, void *this)
{
	while (find->top)
	{
		if (this < (void*)find->top->med)
			return ((get_specific_allocation(find, find->top->tny, this)));
		else if (this < (void*)find->top->med_end)
			return ((get_specific_allocation(find, find->top->med, this)));
		find->top = find->top->next;
	}
	ft_dprintf(2, "Realloc: something went very wrong\n");
	return (0);
}

static int	search_big_nodes(t_alloc *find, void *this)
{
	find->inside = find->head->large;
	while (find->inside)
	{
		if (find->inside->user_data == this)
		{
			ft_printf("Realloc: large section %p\n", find->inside->user_data);
			return (1);
		}
		find->inside = find->inside->next;
	}
	return (0);
}

static int	find_malloc(t_alloc *find, void *this)
{
	if (search_big_nodes(find, this))
		return (1);
	if (search_small_nodes(find, this))
		return (1);
	return (0);
}

void		*realloc(void *this, size_t size)
{
	t_alloc		find;
	void		*new;

	if (size == 0)
	{
		free(this);
		return (NULL);
	}
	else if (!this)
		return ((this = malloc(size)));
	find.inside = NULL;
	find.head = get_head();
	find.top = find.head;
	if (!find_malloc(&find, this))
		return (NULL);
	new = malloc(size);
	if (find.inside->user_size <= size)
		new = ft_memcpy(new, find.inside->user_data, find.inside->user_size);
	else
		new = ft_memcpy(new, find.inside->user_data, size);
	free(this);
	return (new);
}
