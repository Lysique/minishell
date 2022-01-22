/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:57:15 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/22 15:42:30 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_all(t_list *allocated)
{
	t_list	*tmp;

	tmp = allocated;
	while (tmp)
	{
		allocated = allocated->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
		tmp = allocated;
	}
}

void	ft_free(t_list *allocated, void *p)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = allocated;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp2->content == p)
		{
			tmp->next = tmp2->next;
			free(tmp2->content);
			free(tmp2);
			return ;
		}
		tmp = tmp->next;
	}
	printf("Pointer being freed is not on the list");
	ft_free_all(allocated);
	exit(EXIT_FAILURE);
}

void	*ft_allocs(t_list *allocated, int size)
{
	t_list	*tmp;
	t_list	*new;

	tmp = allocated;
	while (tmp->next)
		tmp = tmp->next;
	new = malloc(sizeof(t_list));
	ft_bzero(new, sizeof(t_list));
	if (!new)
	{
		ft_free_all(allocated);
		exit(EXIT_FAILURE);
	}
	new->content = malloc(size);
	ft_bzero(new->content, size);
	if (!new->content)
	{
		ft_free_all(allocated);
		exit(EXIT_FAILURE);
	}
	new->next = 0;
	tmp->next = new;
	return (new->content);
}

void	*ft_malloc(int size, void *p)
{
	static t_list	*allocated = 0;

	if (!allocated)
	{
		allocated = malloc(sizeof(t_list));
		allocated->next = 0;
		allocated->content = 0;
	}
	if (size == -1)
		ft_free(allocated, p);
	else if (size == -2)
	{
		ft_free_all(allocated);
		allocated = 0;
	}
	else
		return (ft_allocs(allocated, size));
	return (0);
}
