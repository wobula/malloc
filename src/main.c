/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/06 14:06:23 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <sys/resource.h>

#define tnysize 100
#define medsize 500

t_node	*head = NULL;

t_data	*allocate_data(t_data *start, int capacity, size_t node_count, int storage_size)
{
	t_data *tmp;

	tmp = start;
	while (node_count > 0)
	{
		tmp->data = (void*)(tmp + 1);
		tmp->next = (t_data*)((char*)tmp->data + storage_size);
		tmp->available = 1;
		node_count--;
		capacity -= (sizeof(t_data) + storage_size);
		ft_printf("tny data    : %p\n", tmp->data);
		ft_printf("tmp->next   : %p\n", tmp->next);
		ft_printf("tny capacity: %d\n", capacity);
		ft_printf("tny node cot: %d\n", node_count);
		tmp = tmp->next;
	}
	tmp->next = NULL;
	return (tmp);	
}

t_node	*get_head()
{
	int get_size;
	int data;

	if (!head)
	{
		get_size = sizeof(t_node) +
					((tnysize + sizeof(t_data)) * 100) +
					((medsize + sizeof(t_data)) * 100);
		data = 0;
		while (data < get_size)
			data = data + getpagesize();
		head = mmap(NULL, data, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		head->available = data - (sizeof(t_node) + sizeof(t_data));
		head->tny = (t_data*)(head + 1);
		head->tny_size = (sizeof(t_data) + tnysize) * 100;
		head->tny_end = allocate_data(head->tny, head->tny_size, 100, tnysize);
		head->med = (t_data*)(((char*)(head->tny_end + 1)) + tnysize);
		head->med_size = (sizeof(t_data) + medsize) * 100;
		head->med_end = allocate_data(head->med, head->med_size, 100, medsize);
		ft_printf("med start: %p\n", head->med);
	}
	return(head);
}

void	 *malloc(size_t size)
{
	t_node 	*ptr;
	t_data 	*tmp;
	
	ft_putnbr(size);
	ptr = get_head();
	if (size > tnysize)
		tmp = ptr->med;
	else
		tmp = ptr->tny;
	while (tmp)
	{
		if (tmp->available == 1)
			break ;
		tmp = tmp->next;
	}
	if (tmp->available == 0)
		return (NULL);
	return (tmp->data);
}

int		main(void)
{
	void *ptr;

	ptr = malloc(50);
	ft_printf("head node: %p\n", head);
	ft_printf("available: %d\n", head->available);
	ft_printf("tny node : %p\n", ptr);
	return (0);
}
