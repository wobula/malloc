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

void	 free(void *this)
{
	t_node *ptr;
	t_data *tmp;
	size_t *allocations;

	ptr = get_head();
	if (check_big_nodes(ptr, this))
		return ;
	if (this < (void*)ptr->tny_end)
	{
		tmp = ptr->tny;
		allocations = &ptr->tny_allocations;
	}
	else if (this < (void*)ptr->med_end)
	{
		tmp = ptr->med;
		allocations = &ptr->med_allocations;
	}
	else
	{
		ft_printf("Pointer being freed was not allocated\n");
		return ;
	}
	while (tmp->next)
	{
		if (tmp->data == this)
		{
			ft_printf("Pointer found at address %p\n", tmp->data);
			if (tmp->available == 0)
			{
				tmp->available = 1;
				*allocations = *allocations + 1;
				ft_printf("Pointer freed at address %p\n", tmp->data);
			}
			else
				ft_printf("Pointer found is already freed\n");
			break ;
		}
		tmp = tmp->next;
	}
}