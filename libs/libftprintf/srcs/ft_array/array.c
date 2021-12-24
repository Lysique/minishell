/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:34:06 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/24 06:06:16 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"

/*Initializes/mallocs array to hold items of 'item_size' */
void	ft_array_init(t_array *a, size_t item_size)
{
	a->size = 4;
	a->item_size = item_size;
	a->count = 0;
	a->data = ft_calloc(a->size, a->item_size);
}

/*returns void *content at index i*/
void	*ft_array_get(t_array *a, int i)
{
	if ((unsigned int)i >= a->count)
		return (0);
	return ((char *)a->data + i * a->item_size);
}

/*Doubles array size*/
static void	*ft_array_extend(t_array *a)
{
	a->size *= 2;
	a->data = ft_realloc(a->data,
			a->size * a->item_size,
			a->count * a->item_size);
	return (a->data);
}

/*adds void *content to back of array, doubling array size
	when array limit reached
*/
void	*ft_array_add(t_array *a, void *content)
{
	if (a->count == a->size - 1)
		if (!ft_array_extend(a))
			return (0);
	ft_memcpy((char *)a->data + a->item_size * a->count, content, a->item_size);
	a->count++;
	return ((char *)a->data + a->item_size * (a->count - 1));
}

/*Frees all data pointers in array*/
void	ft_array_del(t_array *a)
{
	free(a->data);
}
