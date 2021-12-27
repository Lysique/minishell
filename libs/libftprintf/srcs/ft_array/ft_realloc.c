/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:32:04 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/24 06:05:34 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"

/*Will allocate new_size, copy ptr contents of old_size, free ptr and return 
 a pointer to the copy of new_size*/
void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*ret;

	ret = ft_calloc(new_size, 1);
	if (ret)
		ft_memcpy(ret, ptr, old_size);
	free(ptr);
	return (ret);
}
