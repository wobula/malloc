/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/06 13:11:11 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include "../libft/includes/libft.h"

typedef struct				s_node
{
	struct s_node			*next;
	int						size;
	int						available;
	size_t					count;
	struct s_data			*tny;
	struct s_data			*tny_end;
	int						tny_size;
	struct s_data			*med;
	struct s_data			*med_end;
	int						med_size;
}							t_node;

typedef struct				s_data
{
	struct s_data			*next;
	int						size;
	int						available;
	void					*data;
}							t_data;

void	*malloc(size_t size);

#endif
