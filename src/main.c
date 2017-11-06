/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/06 13:06:01 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <sys/resource.h>

#define tny_size 100
#define med_size 500

t_node	*head = NULL;

void	 *malloc(size_t size)
{
	t_node *ptr;

	if (!head)
	{
		head = mmap(NULL, sizeof(t_node) +
							getpagesize() * 100 * tny_size,
							PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		head->size = size;
		head->available = getpagesize() * 100 * tny_size - sizeof(t_node);
		head->tny = (t_data*)(head + 1);
		ptr = head;
	}
	ptr = head;
	return (ptr);
}

int		main(void)
{
	t_node *head;

	head = (t_node*)malloc(50);
	ft_printf("head node: %p\n", head);
	ft_printf("available: %d\n", head->available);
	ft_printf("tny node : %p\n", head->tny);
	return (0);
}
