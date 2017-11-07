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
	t_malloc help;

	help.ptr = get_head();
	if (check_big_nodes(help.ptr, this))
		return ;
	if (this < (void*)help.ptr->tny_end)
	{
		help.tmp = help.ptr->tny;
		help.allocations = &help.ptr->tny_allocations;
	}
	else if (this < (void*)help.ptr->med_end)
	{
		help.tmp = help.ptr->med;
		help.allocations = &help.ptr->med_allocations;
	}
	else
	{
		ft_printf("Pointer being freed was not allocated\n");
		return ;
	}
	while (help.tmp->next)
	{
		if (help.tmp->data == this)
		{
			ft_printf("Pointer found at address %p\n", help.tmp->data);
			if (help.tmp->available == 0)
			{
				help.tmp->available = 1;
				*help.allocations = *help.allocations + 1;
				ft_printf("Pointer freed at address %p\n", help.tmp->data);
			}
			else
				ft_printf("Pointer found is already freed\n");
			break ;
		}
		help.tmp = help.tmp->next;
	}
}