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
	char	*ptr;
	char	*ptr2;
	char	*ptr3;

	ptr = NULL;
	ptr = realloc(ptr, 600);
	ptr2 = malloc(50);
	ptr3 = malloc(400);
	free(ptr);
	free(ptr2);
	free(ptr3);
	return (0);
}
