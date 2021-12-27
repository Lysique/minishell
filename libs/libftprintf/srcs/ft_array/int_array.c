/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:06:55 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/03 13:22:19 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"

void	ft_int_array_init(t_int_array *a)
{
	a->size = 4;
	a->count = 0;
	a->data = malloc(a->size * sizeof(int));
}

int	ft_int_array_get(t_int_array *a, int i, int default_v)
{
	if ((unsigned int)i >= a->count)
		return (default_v);
	return (a->data[i]);
}

static void	*ft_int_array_extend(t_int_array *a)
{
	a->size *= 2;
	a->data = ft_realloc(a->data,
			 a->size * sizeof(int),
			 a->count * sizeof(int));
	return (a->data);
}

int	ft_int_array_add(t_int_array *a, int v)
{
	if (a->count == a->size - 1)
		if (!ft_int_array_extend(a))
			return (0);
	a->data[a->count] = v;
	return (++a->count);
}

void	ft_int_array_del(t_int_array *a)
{
	free(a->data);
}
