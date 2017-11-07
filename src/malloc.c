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

void	 *malloc(size_t size)
{
	t_node 	*ptr;
	t_data 	*tmp;
	size_t  *allocations;

	tmp = NULL;
	ptr = get_head();
	while (ptr)
	{
		if (size <= tnysize && ptr->tny_allocations > 0)
		{
			tmp = ptr->tny;
			allocations = &ptr->tny_allocations;
			break ;
		}
		else if (size <= medsize && ptr->med_allocations > 0)
		{
			tmp = ptr->med;
			allocations = &ptr->med_allocations;
			break ;
		}
		if (!ptr->next)
			ptr->next = expand_head();
		ptr = ptr->next;
	}
	if (!tmp)
	{
		ft_printf("Your pointer was");
	}
	while (tmp->next)
	{
		if (tmp->available == 1)
		{
			tmp->available = 0;
			*allocations = *allocations - 1;
			ft_printf("Malloc: you have %d allocations leftover\n", *allocations);
			ft_printf("Malloc: Using free pointer address %p\n", tmp);
			//ft_printf("id: %d\n", tmp->id);
			return (tmp->data);
		}
		tmp = tmp->next;
	}
	return (NULL);
}