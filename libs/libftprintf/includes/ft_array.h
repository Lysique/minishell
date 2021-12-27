/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 05:40:44 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/24 06:01:23 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARRAY_H
# define FT_ARRAY_H

# include <stdlib.h>
# include "ft_printf_bonus.h"

typedef struct s_array
{
	size_t	item_size;
	size_t	count;
	size_t	size;
	void	*data;
}				t_array;

typedef struct s_int_array
{
	size_t	count;
	size_t	size;
	int		*data;
}				t_int_array;

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size);

	/* Generic arrays */

/*Initializes/mallocs array to hold items of 'item_size' */
void	ft_array_init(t_array *a, size_t item_size);
/*returns void *content at index i*/
void	*ft_array_get(t_array *a, int i);
/*adds void *content to back of array, doubling array size
	when array limit reached*/
void	*ft_array_add(t_array *a, void *content);
/*Frees all data pointers in array*/
void	ft_array_del(t_array *a);

	/* Integer arrays*/

/*Initializes/mallocs array to hold items of size int */
void	ft_int_array_init(t_int_array *a);
/*returns integer value of content at index i*/
int		ft_int_array_get(t_int_array *a, int i, int default_v);
/*adds integer value to content pointer to back of array, doubling array size
	when array limit reached*/
int		ft_int_array_add(t_int_array *a, int v);
/*Frees all data pointers in array*/
void	ft_int_array_del(t_int_array *a);

#endif