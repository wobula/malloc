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

	ptr = get_head();
	if (size <= tnysize)
		tmp = ptr->tny;
	else if (size <= medsize)
		tmp = ptr->med;
	else
		return (NULL);
	while (tmp->next)
	{
		if (tmp->available == 1)
		{
			tmp->available = 0;
			ft_printf("Using free pointer address at %p\n", tmp);
			ft_printf("id: %d\n", tmp->id);
			return (tmp->data);
		}
		tmp = tmp->next;
	}
	return (NULL);
}