/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:27:27 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/28 14:52:21 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_srch(char *envp, char *var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (envp[i] != var[i])
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
