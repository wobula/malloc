/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdbool.h>
# include "../includes/libft.h"

# define NUMBERSET "0123456789abcdef0123456789ABCDEF"
# define COLORRESET "\e[0m"
# define COLORSTART "\e["
# define COLORFINISH "m"

typedef struct				s_print
{
	int						fd;
	int						ret;
	char					*format;
	va_list					arg;
}							t_print;

typedef union
{
	char					chr;
	char					*str;
	intmax_t				super;
	uintmax_t				super_u;
	void					*ptr;
}							t_raw;

typedef struct				s_spec
{
	bool					alt_form;
	bool					left_align;
	bool					prepend_space;
	bool					prepend_zero;
	bool					show_sign;
	char					length[3];
	char					type;
	int						len;
	int						precision;
	int						width;
	int						max;
	int						*ret;
	int						*fd;
	va_list					*arg;
	t_raw					data;
}							t_spec;

typedef struct				s_format
{
	char					sign;
	char					*print;
	int						length;
	int						spaces;
	int						zeroes;
}							t_format;

void						parse(t_print *ptr);
int							gather_flags(t_spec *this, char *format, int *x);
int							specifier(t_spec *this, char c);
int							precision(t_spec *this, char *format);
int							width(t_spec *this, char *format);
int							length(t_spec *this, char *format);
int							flags(t_spec *this, char *format);
int							ft_isflag(char test);
int							colors(t_spec *this);
int							max(t_spec *this, char *format);

void						conversions(t_print *ptr, t_spec *this);
void						conversions_u(t_print *ptr, t_spec *this);

void						format_char(t_print *ptr, t_spec *this);
void						format_percent(t_spec *this);
void						format_string(t_print *ptr, t_spec *this);
void						format_decimal(t_print *ptr, t_spec *this);
void						format_udecimal(t_print *ptr, t_spec *this);
void						format_pointer(t_print *ptr, t_spec *this);
void						format_octal(t_print *ptr, t_spec *this);
void						format_hex(t_print *ptr, t_spec *this);

char						*ft_ptf_itoabase(uintmax_t val, int base, int opt);

#endif
