/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 11:02:43 by slathouw          #+#    #+#             */
/*   Updated: 2021/10/11 10:20:36 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elm;

	elm = (t_list *) ft_calloc(sizeof(t_list), 1);
	if (!elm)
		return (NULL);
	elm->content = content;
	elm->next = NULL;
	return (elm);
}
