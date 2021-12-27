/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:27:27 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/26 11:28:00 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_srch(char *envp)
{
	int		i;
	int		j;
	char	*path;

	path = "PATH=";
	i = 0;
	j = 4;
	while (i <= j)
	{
		if (envp[i] != path[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_check(char s1, char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}
