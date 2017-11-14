/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_char                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	print_width(t_spec *this)
{
	int print;

	print = this->width - this->len;
	while (print > 0)
	{
		ft_putchar_fd(*this->fd, ' ');
		print--;
		*this->ret = *this->ret + 1;
	}
}

static void	print_char(char output, int *ret, int fd)
{
	ft_putchar_fd(output, fd);
	*ret = *ret + 1;
}

void		format_char(t_print *ptr, t_spec *this)
{
	this->data.chr = (char)va_arg(ptr->arg, int);
	this->len = 1;
	if (this->left_align == true)
	{
		print_char(this->data.chr, this->ret, *this->fd);
		print_width(this);
	}
	else
	{
		print_width(this);
		print_char(this->data.chr, this->ret, *this->fd);
	}
}
