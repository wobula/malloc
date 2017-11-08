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

# define TNYSIZE 100
# define MEDSIZE 500

typedef struct		s_node
{
	struct s_node	*next;
	size_t			count;
	struct s_data	*tny;
	struct s_data	*tny_end;
	size_t			tny_allocations;
	int				tny_size;
	struct s_data	*med;
	struct s_data	*med_end;
	size_t			med_allocations;
	int				med_size;
	struct s_data	*large;
}					t_node;

typedef struct		s_data
{
	struct s_data	*next;
	size_t			available;
	size_t			size;
	void			*data;
}					t_data;

typedef struct		s_malloc
{
	t_node			*ptr;
	t_data			*tmp;
	size_t			*allocations;
}					t_malloc;

typedef struct 		s_realloc
{
	t_node			*top;
	t_data			*inside;
	t_data			*prev;
	size_t			*allocations;
} 					t_realloc;

void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				free(void *ptr);

t_data				*allocate_data(t_data *start, size_t count, int size);
t_node				*get_head();
t_node				*expand_head();

#endif
