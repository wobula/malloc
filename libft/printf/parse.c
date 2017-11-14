/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	constructor(t_print *ptr, t_spec *this)
{
	this->left_align = false;
	this->show_sign = false;
	this->prepend_space = false;
	this->prepend_zero = false;
	this->alt_form = false;
	this->width = 0;
	this->precision = -1;
	this->length[0] = '\0';
	this->length[1] = '\0';
	this->length[2] = '\0';
	this->type = 0;
	this->len = 0;
	this->max = -1;
	this->arg = &ptr->arg;
	this->fd = &ptr->fd;
	this->ret = &ptr->ret;
}

static void	activate_frankenstein(t_print *ptr, int *xptr)
{
	t_spec this;

	constructor(ptr, &this);
	gather_flags(&this, ptr->format, xptr);
	if (this.type == 's' || this.type == 'S')
		format_string(ptr, &this);
	else if (this.type == 'd')
		format_decimal(ptr, &this);
	else if (this.type == 'c' || this.type == 'C')
		format_char(ptr, &this);
	else if (this.type == '%')
		format_percent(&this);
	else if (this.type == 'p')
		format_pointer(ptr, &this);
	else if (this.type == 'o')
		format_octal(ptr, &this);
	else if (this.type == 'x' || this.type == 'X')
		format_hex(ptr, &this);
	else if (this.type == 'u')
		format_udecimal(ptr, &this);
}

static void	print_buffer(t_print *ptr, int start, int x)
{
	write(ptr->fd, ptr->format + start, x - start);
	ptr->ret += x - start;
}

void		parse(t_print *ptr)
{
	int x;
	int start;

	x = -1;
	start = 0;
	while (ptr->format[++x] != '\0')
	{
		if (ptr->format[x] == '%')
		{
			print_buffer(ptr, start, x);
			activate_frankenstein(ptr, &x);
			start = x + 1;
		}
	}
	print_buffer(ptr, start, x);
}
