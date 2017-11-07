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

void	*allocate_found_node(t_malloc *find)
{
	while (find->tmp->next)
	{
		if (find->tmp->available == 1)
		{
			find->tmp->available = 0;
			*find->allocations = *find->allocations - 1;
			ft_printf("Malloc: you have %d allocations leftover\n",
				*find->allocations);
			ft_printf("Malloc: Using free pointer address %p\n", find->tmp);
			break ;
		}
		find->tmp = find->tmp->next;
	}
	return (find->tmp->data);
}

void	*find_small_node(t_malloc *find, size_t size)
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
	return (allocate_found_node(find));
}

t_data	*allocate_big_node(size_t size)
{
	t_data	*this;
	int		get_data;

	get_data = getpagesize();
	while ((int)(size + sizeof(t_data)) > get_data)
		get_data += getpagesize();
	this = mmap(NULL, get_data,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	this->size = get_data;
	this->next = NULL;
	this->data = this + 1;
	ft_printf("Allocated %d to address :%p\n", this->size, this);
	ft_printf("Data address for pointer:%p\n", this->data);
	return (this);
}

void	*find_big_node(t_malloc *find, size_t size)
{
	t_data *this;

	if (!find->ptr->large)
	{
		this = allocate_big_node(size);
		find->ptr->large = this;
		return (this->data);
	}
	else
	{
		this = find->ptr->large;
		while (this->next && this->available == 0)
			this = this->next;
		this->next = allocate_big_node(size);
		return (this->next->data);
	}
	return (NULL);
}

void	*malloc(size_t size)
{
	t_malloc find;

	find.tmp = NULL;
	find.ptr = get_head();
	if (size <= medsize)
		return (find_small_node(&find, size));
	else
		return (find_big_node(&find, size));
	return (NULL);
}
