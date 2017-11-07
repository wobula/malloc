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

void	 free(void *ptr)
{
	t_node *tmp;
	t_data *find;
	size_t *allocations;

	ft_printf("freeing ptr address: %p\n", ptr);
	tmp = get_head();
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