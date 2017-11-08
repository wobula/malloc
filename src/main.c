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

int		main(void)
{
	char	*ptr2;
	char	*ptr;
	char 	*ptr3;

	ptr2 = malloc(10);
	ptr3 = malloc(101);
	ptr = malloc(5000);
	realloc(ptr2, 101);
	realloc(ptr, 10);
	realloc(ptr3, 5000);
	free(ptr2);
	return (0);
}
