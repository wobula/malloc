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

void	find_free_node(t_malloc *find, size_t size)
{
	while (find->ptr)
	{
		if (size <= tnysize && find->ptr->tny_allocations > 0)
		{
			find->tmp = find->ptr->tny;
			find->allocations = &find->ptr->tny_allocations;
			break ;
		}
		else if (size <= medsize && find->ptr->med_allocations > 0)
		{
			find->tmp = find->ptr->med;
			find->allocations = &find->ptr->med_allocations;
			break ;
		}
		if (!find->ptr->next)
			find->ptr->next = expand_head();
		find->ptr = find->ptr->next;
	}
}

void	 *malloc(size_t size)
{
	t_malloc find;

	find.tmp = NULL;
	find.ptr = get_head();
	find_free_node(&find, size);
	if (!find.tmp)
	{
		ft_printf("Your pointer was");
	}
	while (find.tmp->next)
	{
		if (find.tmp->available == 1)
		{
			find.tmp->available = 0;
			*find.allocations = *find.allocations - 1;
			ft_printf("Malloc: you have %d allocations leftover\n", *find.allocations);
			ft_printf("Malloc: Using free pointer address %p\n", find.tmp);
			//ft_printf("id: %d\n", tmp->id);
			return (find.tmp->data);
		}
		find.tmp = find.tmp->next;
	}
	return (NULL);
}