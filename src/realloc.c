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

int 	search_big_nodes(t_realloc *find, void *this)
{
	t_data *tmp;

	tmp = find->top->large;
	find->prev = NULL;
	while (tmp)
	{
		if (tmp->data == this)
		{
			find->inside = tmp;
			ft_printf("Realloc: found your big malloc at %p\n", find->inside);
			return (1);
		}
		find->prev = tmp;
		tmp = tmp->next;
	}
	find->prev = NULL;
	return (0);
}

//int search_small_ndoes()

int		find_malloc(t_realloc *find, void *this)
{
	if (search_big_nodes(find, this))
		return (1);
	//else if (search_small_nodes(find, this))
	//	return (1);
	return (0);
}

void	*realloc(void *this, size_t size)
{
	t_realloc find;

	if (size == 0)
	{
		free(this);
		return (NULL);
	}
	else if (!this)
		return ((this = malloc(size)));
	find.inside = NULL;
	find.top = get_head();
	if (find_malloc(&find, this))
		ft_printf("Realloc: found your big malloc at %p\n", find.inside);
	return (this);
}
