/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/06 14:06:23 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		*allocate_found_node(t_alloc *find, size_t size)
{
	while (find->inside->next)
	{
		if (find->inside->available == 1)
		{
			find->inside->available = 0;
			find->inside->size = size;
			*find->allocations = *find->allocations - 1;
			ft_printf("Malloc: you have %d allocations leftover\n",
				*find->allocations);
			ft_printf("Malloc: Using free pointer address %p\n", find->inside);
			break ;
		}
		find->inside = find->inside->next;
	}
	return (find->inside->data);
}

static void		*find_small_node(t_alloc *find, size_t size)
{
	while (find->top)
	{
		if (size <= TNYSIZE && find->top->tny_allocations > 0)
		{
			find->inside = find->top->tny;
			find->allocations = &find->top->tny_allocations;
			break ;
		}
		else if (size <= MEDSIZE && find->top->med_allocations > 0)
		{
			find->inside = find->top->med;
			find->allocations = &find->top->med_allocations;
			break ;
		}
		if (!find->top->next)
			find->top->next = expand_head();
		find->top = find->top->next;
	}
	return (allocate_found_node(find, size));
}

static t_data	*allocate_big_node(size_t size)
{
	t_data	*tmp;
	int		get_data;

	get_data = getpagesize();
	while ((int)(size + sizeof(t_data)) > get_data)
		get_data += getpagesize();
	tmp = mmap(NULL, get_data,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp->size = get_data;
	tmp->big_size = size;
	tmp->next = NULL;
	tmp->data = tmp + 1;
	ft_printf("Malloc: Allocated %d to address :%p\n", size, tmp->big_size);
	ft_printf("Malloc: Data address for pointer:%p\n", tmp->data);
	return (tmp);
}

static void		*find_big_node(t_alloc *find, size_t size)
{
	t_data *tmp;

	if (!find->top->large)
	{
		tmp = allocate_big_node(size);
		find->top->large = tmp;
		return (tmp->data);
	}
	else
	{
		tmp = find->top->large;
		while (tmp->next && tmp->available == 0)
			tmp = tmp->next;
		tmp->next = allocate_big_node(size);
		return (tmp->next->data);
	}
	return (NULL);
}

void			*malloc(size_t size)
{
	t_alloc find;

	find.inside = NULL;
	find.top = get_head();
	ft_printf("hi: %zu\n", size);
	if (size <= MEDSIZE)
		return (find_small_node(&find, size));
	else
		return (find_big_node(&find, size));
	return (NULL);
}
