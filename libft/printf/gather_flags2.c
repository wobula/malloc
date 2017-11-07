/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	colors(t_spec *this)
{
	int color;

	color = va_arg(*this->arg, int);
	ft_fputstr_fd(COLORSTART, *this->fd);
	ft_putnbr_fd(color, *this->fd);
	ft_fputstr_fd(COLORFINISH, *this->fd);
	return (0);
}

int	ft_isflag(char test)
{
	if (test == '#' || test == '-' || test == '+' ||
		test == '0' || test == ' ')
		return (1);
	return (0);
}

int	flags(t_spec *this, char *format)
{
	int x;

	x = -1;
	while (ft_isflag(format[++x]))
	{
		if (format[x] == '#')
			this->alt_form = true;
		else if (format[x] == ' ')
			this->prepend_space = true;
		else if (format[x] == '0')
			this->prepend_zero = true;
		else if (format[x] == '+')
			this->show_sign = true;
		else if (format[x] == '-')
			this->left_align = true;
	}
	return (x - 1);
}

int	length(t_spec *this, char *format)
{
	int c;

	c = 0;
	if (format[c] == 'h' && format[c + 1] == 'h' && (c = c + 2))
		ft_strcpy(this->length, "hh\0");
	else if (format[c] == 'h' && (c = c + 1))
		ft_strcpy(this->length, "h\0");
	else if (format[c] == 'l' && format[c + 1] == 'l' && (c = c + 2))
		ft_strcpy(this->length, "ll\0");
	else if (format[c] == 'l' && (c = c + 1))
		ft_strcpy(this->length, "l\0");
	else if (format[c] == 'z' && (c = c + 1))
		ft_strcpy(this->length, "z\0");
	else if (format[c] == 'j' && (c = c + 1))
		ft_strcpy(this->length, "j\0");
	return (c - 1);
}
