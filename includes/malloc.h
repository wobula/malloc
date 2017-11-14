/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/11/14 13:08:03 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include "../libft/includes/libft.h"

# define TNYSIZE 100
# define MEDSIZE 500
# define NODECOUNT 100

typedef struct		s_node
{
	struct s_node	*next;
	size_t			slab_count;
	size_t			slab_size;
	struct s_data	*tny;
	struct s_data	*tny_end;
	size_t			tny_allocs;
	size_t			tny_block;
	struct s_data	*med;
	struct s_data	*med_end;
	size_t			med_allocs;
	size_t			med_block;
	struct s_data	*large;
	size_t			large_allocs;
	size_t			frees;
	size_t			freed_bytes;
	size_t			total_allocs;
}					t_node;

typedef struct		s_data
{
	struct s_data	*next;
	size_t			available;
	size_t			user_size;
	size_t			block_size;
	void			*user_data;
}					t_data;

typedef struct		s_alloc
{
	t_node			*head;
	t_node			*top;
	t_node			*prev_node;
	t_data			*inside;
	t_data			*prev;
	size_t			total_alloc_bytes;
	size_t			total_allocs;
	size_t			leaks;
}					t_alloc;

void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				*calloc(size_t nitems, size_t size);
void				free(void *ptr);
void				show_alloc_mem();

void				free_head(void);
t_node				*get_head();
t_node				*slab_carver();

#endif
