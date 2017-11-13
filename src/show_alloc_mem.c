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

static size_t	show_inner_data(t_alloc *show, t_data *inside)
{
	size_t	current_bytes;
	void	*end;

	current_bytes = 0;
	while (inside)
	{
		if (inside->available == 0)
		{
			end = (void*)((char*)(inside + 1)) + inside->user_size;
			ft_dprintf(2, "%p - %p : ", inside, end);
			ft_dprintf(2, "%zu bytes\n", inside->user_size);
			current_bytes += inside->user_size;
			show->total_allocs++;
		}
		inside = inside->next;
	}
	return (current_bytes);
}

static void		print_smaller_allocs(t_alloc *show, char *context, int opt)
{
	size_t current_bytes;

	current_bytes = 0;
	show->top = show->head;
	if (opt == 0)
		ft_dprintf(2, "%s %=5p\n", context, show->head->tny);
	else
		ft_dprintf(2, "%s %=5p\n", context, show->head->med);
	while (show->top)
	{
		if (opt == 0)
			show->inside = show->top->tny;
		else
			show->inside = show->top->med;
		current_bytes += show_inner_data(show, show->inside);
		show->top = show->top->next;
	}
	show->total_alloc_bytes = show->total_alloc_bytes + current_bytes;
	ft_dprintf(2, "%s SUMMARY : %d bytes\n\n", context, current_bytes);
}

static void		print_large_allocs(t_alloc *show, char *context)
{
	size_t	current_bytes;
	void	*end;

	current_bytes = 0;
	show->inside = show->head->large;
	ft_dprintf(2, "%s %=5p\n", context, show->head->large);
	while (show->inside)
	{
		end = (void*)((char*)(show->inside + 1)) + show->inside->user_size;
		current_bytes += show->inside->user_size;
		show->total_allocs++;
		ft_dprintf(2, "%p - %p : ", show->inside, end);
		ft_dprintf(2, "%zu bytes\n", show->inside->user_size);
		show->inside = show->inside->next;
	}
	ft_dprintf(2, "%s SUMMARY : %d bytes\n\n", context, current_bytes);
	show->total_alloc_bytes = show->total_alloc_bytes + current_bytes;
}

void			show_alloc_mem(void)
{
	t_alloc show;
	size_t	total_memory;

	show.head = get_head();
	show.total_allocs = 0;
	show.total_alloc_bytes = 0;
	show.leaks = show.head->total_allocs - show.head->frees;
	ft_printf("total allocs: %d\n", show.head->total_allocs);
	ft_dprintf(2, "\nShow_alloc_mem: Malloc Info\n\n");
	print_smaller_allocs(&show, "TINY :", 0);
	print_smaller_allocs(&show, "MED :", 1);
	print_large_allocs(&show, "LARGE :");
	total_memory = show.head->freed_bytes + show.total_alloc_bytes;
	ft_dprintf(2, "OVERALL SUMMARY:\n");
	ft_dprintf(2, "Total allocs         : %zu\n", show.head->total_allocs);
	ft_dprintf(2, "Total frees          : %zu\n", show.head->frees);
	ft_dprintf(2, "Total leaks          : %zu\n", show.leaks);
	ft_dprintf(2, "Total unfreed bytes  : %zu\n", show.total_alloc_bytes);
	ft_dprintf(2, "Total freed bytes    : %zu\n", show.head->freed_bytes);
	ft_dprintf(2, "Total memory used    : %zu\n", total_memory);
}
