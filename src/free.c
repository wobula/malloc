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

int		check_big_nodes(t_node *check, void *ptr)
{
	t_data *tmp;
	t_data *prev;

	if (!check->large)
		return (0);
	tmp = check->large;
	prev = NULL;
	while (tmp->next)
	{
		if (tmp->data == ptr)
			break ;
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp->data == ptr)
	{
		if (prev)
			prev->next = tmp->next;
		munmap(&tmp, tmp->size);
		return (1);
	}
	return (0);
}

int		check_smaller_nodes(t_alloc *find, void *this)
{
	if (this < (void*)find->top->tny_end)
	{
		find->inside = find->top->tny;
		find->allocations = &find->top->tny_allocations;
		return (1);
	}
	else if (this < (void*)find->top->med_end)
	{
		find->inside = find->top->med;
		find->allocations = &find->top->med_allocations;
		return (1);
	}
	return (0);
}

int		free_smaller_node(t_alloc *find, void *this)
{
	while (find->inside->next)
	{
		if (find->inside->data == this)
		{
			if (find->inside->available == 0)
			{
				find->inside->available = 1;
				*find->allocations = *find->allocations + 1;
				return (1);
			}
			else
				ft_printf("Free: Pointer found is already free\n");
			break ;
		}
		find->inside = find->inside->next;
	}
	return (0);
}

void	free(void *this)
{
	t_alloc find;

	find.top = get_head();
	if (check_big_nodes(find.top, this))
		return ;
	if (check_smaller_nodes(&find, this))
		free_smaller_node(&find, this);
	else
		ft_printf("Free: Pointer being freed was not allocated\n");
}
