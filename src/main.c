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
	char 	*ptr;
	char 	*ptr2;
	char 	*ptr3;
	char 	*ptr4;
	char 	*ptr5;
	char 	*ptr6;
	char 	*ptr7;
	char 	*ptr8;

	ptr = malloc(600);
	ptr2 = malloc(600);
	ptr3 = malloc(600);
	ptr4 = malloc(600);
	ptr5 = malloc(600);
	ptr6 = malloc(600);
	ptr7 = malloc(600);
	ptr8 = malloc(600);

	free(ptr);
	free(ptr2);
	free(ptr3);
	free(ptr4);
	free(ptr5);
	free(ptr6);
	free(ptr7);
	free(ptr8);
	return (0);
}
