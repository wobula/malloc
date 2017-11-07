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
		ft_printf("address range has %d size\n", tmp->size);
		ft_printf("Freed pointer at node address %p\n", tmp);
		return (1);
	}
	return (0);
}

void	 free(void *ptr)
{
	t_node *tmp;
	t_data *find;
	size_t *allocations;

	tmp = get_head();
	if (check_big_nodes(tmp, ptr))
		return ;
	if (ptr < (void*)tmp->tny_end)
	{
		find = tmp->tny;
		allocations = &tmp->tny_allocations;
	}
	else if (ptr < (void*)tmp->med_end)
	{
		find = tmp->med;
		allocations = &tmp->med_allocations;
	}
	else
	{
		ft_printf("Pointer being freed was not allocated\n");
		return ;
	}
	while (find->next)
	{
		if (find->data == ptr)
		{
			ft_printf("Pointer found at address %p\n", find->data);
			if (find->available == 0)
			{
				find->available = 1;
				*allocations = *allocations + 1;
				ft_printf("Pointer freed at address %p\n", find->data);
			}
			else
				ft_printf("Pointer found is already freed\n");
			break ;
		}
		find = find->next;
	}
}