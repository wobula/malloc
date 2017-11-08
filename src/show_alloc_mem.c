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

static void	print_allocations(t_alloc *find_mem, char *context)
{
	printf("%s %p\n", context, find_mem->inside);
	find_mem->current_total = 0;
	while (find_mem->inside)
	{
		if (find_mem->inside->size != 0 && find_mem->inside->available == 0)
		{
			printf("%p - %p : %zu bytes\n", find_mem->inside->data,
				(void*)((char*)find_mem->inside->data) + find_mem->inside->size, find_mem->inside->size);
			find_mem->current_total = find_mem->current_total + find_mem->inside->size;
			find_mem->total = find_mem->total + find_mem->inside->size;
		}
		find_mem->inside = find_mem->inside->next;
	}
	ft_printf("SUMMARY - %s total - %d bytes\n", context, find_mem->current_total);
	ft_putchar('\n');
}

static void	print_large_allocations(t_alloc *find_mem, char *context)
{
	printf("%s %p\n", context, find_mem->inside);
	find_mem->current_total = 0;
	while (find_mem->inside)
	{
		if (find_mem->inside->size != 0)
		{
			printf("%p - %p : %zu bytes\n", find_mem->inside->data,
				(void*)((char*)find_mem->inside->data) + find_mem->inside->size, find_mem->inside->big_size);
			find_mem->current_total = find_mem->current_total + find_mem->inside->big_size;
			find_mem->total = find_mem->total + find_mem->inside->big_size;
		}
		find_mem->inside = find_mem->inside->next;
	}
	ft_printf("SUMMARY - %s total - %d bytes\n", context, find_mem->current_total);
	ft_putchar('\n');
}

void		show_alloc_mem()
{
	t_alloc find_mem;

	find_mem.top = get_head();
	find_mem.total = 0;
	while (find_mem.top)
	{
		ft_printf("Head address: %p\n\n", find_mem.top);
		find_mem.inside = find_mem.top->tny;
		print_allocations(&find_mem, "TINY: ");

		find_mem.inside = find_mem.top->med;
		print_allocations(&find_mem, "SMALL: ");

		find_mem.inside = find_mem.top->large;
		print_large_allocations(&find_mem, "LARGE: ");

		find_mem.top = find_mem.top->next;
	}
	ft_printf("OVERALL SUMMARY: %d bytes\n", find_mem.total);
}