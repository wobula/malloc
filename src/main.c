/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/06 13:34:36 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <sys/resource.h>

#define tnysize 100
#define medsize 500

t_node	*head = NULL;

t_data	*allocate_data(t_data *start, int capacity, size_t node_count)
{
	t_data *tmp;

	tmp = start;
	ft_printf("tny capacity: %d\n", capacity);
	ft_printf("tny node cot: %d\n", node_count);
	return (tmp);	
}

void	 *malloc(size_t size)
{
	t_node *ptr;
	int get_size;
	int data;

	get_size = sizeof(t_node) + ((tnysize + sizeof(t_data)) * 100);
	data = 0;
	while (data < get_size)
		data = data + getpagesize();
	ft_printf("get size: %d, page size: %d\n", get_size, getpagesize());
	ft_printf("get this amount of data in page sizes: %d\n", data);
	if (!head)
	{
		head = mmap(NULL, data, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		head->size = size;
		head->available = data - (sizeof(t_node) + sizeof(t_data));
		head->tny = (t_data*)(head + 1);
		head->tny_size = (sizeof(t_data) + tnysize) * 100;
		head->tny = allocate_data(head->tny, head->tny_size, 100);
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
