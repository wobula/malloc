/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	max(t_spec *this, char *format)
{
	int x;

	x = 0;
	this->max = ft_atoi(format);
	while (ft_isdigit(format[++x]))
		;
	return (x - 1);
}

int	width(t_spec *this, char *format)
{
	int x;

	x = 0;
	this->width = ft_atoi(format);
	while (ft_isdigit(format[++x]))
		;
	return (x - 1);
}

int	precision(t_spec *this, char *format)
{
	int x;

	x = 0;
	if (ft_isdigit(format[x]))
	{
		this->precision = ft_atoi(format);
		while (ft_isdigit(format[++x]))
			;
	}
	else
		this->precision = 0;
	return (x);
}

int	specifier(t_spec *this, char c)
{
	if ((c == 's' || c == 'd' || c == 'i' || c == 'c' || c == '%' || c == 'u'
		|| c == 'n' || c == 'o' || c == 'e' || c == 'e' || c == 'x' || c == 'X'
		|| c == 'p' || c == 'P' || c == 'G' || c == 'g' || c == 'S' || c == 'D'
		|| c == 'C' || c == 'O' || c == 'U') && (this->type = c))
		return (1);
	return (0);
}

int	gather_flags(t_spec *this, char *format, int *x)
{
	while (format[++*x] && !(specifier(this, format[*x])))
	{
		if (ft_isflag(format[*x]))
			*x += flags(this, format + *x);
		else if (format[*x] == '.')
			*x += precision(this, format + *x + 1);
		else if (ft_isdigit(format[*x]))
			*x += width(this, format + *x);
		else if (ft_isalpha(format[*x]))
			*x += length(this, format + *x);
		else if (format[*x] == '=')
			*x += max(this, format + *x + 1);
		else if (format[*x] == '&')
			*x += colors(this);
	}
	return (0);
}
