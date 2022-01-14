/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:04:52 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/08 12:36:49 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expander_count(char *var)
{
	int	i;
	int	nb;
	int	quote;

	nb = 1;
	i = 0;
	while (var[i])
	{
		if (ft_isspace(var[i]))
		{
			nb++;
			while (ft_isspace(var[i]))
				i++;
		}
		if (var[i] == 39 || var[i] == 34)
		{
			quote = var[i];
			while (var[i] && var[i] != quote)
				i++;
		}
		if (var[i])
			i++;
	}
	return (nb);
}

int	ft_countlength(char *var)
{
	int	i;
	int	quote;

	i = 0;
	while (var[i] != ' ' && var[i])
	{
		if (var[i] == 39 || var[i] == 34)
		{
			quote = var[i];
			while (var[i] && var[i] != quote)
				i++;
		}
		if (var[i])
			i++;
	}
	return (i);
}

char	*add_expander_word(char **var)
{
	char	*new;
	int		quote;
	int		i;
	int		j;

	new = ft_malloc(ft_countlength(*var) + 1, 0);
	i = 0;
	j = 0;
	while (*(*var + j) != ' ' && *(*var + j))
	{
		if (*(*var + j) == 39 || *(*var + j) == 34)
		{
			quote = *(*var + j++);
			while (*(*var + j) && *(*var + j) != quote)
				new[i++] = *(*var + j++);
			if (*(*var + j))
				j++;
			continue ;
		}
		if (*(*var + j))
			new[i++] = *(*var + j++);
	}
	new[i] = '\0';
//	printf("NEW : %s\n", new);
	*var += j;
	return (new);
}

char	**expander_split(char *var)
{
	int		j;
	char	**new;

	j = 0;
	new = ft_malloc(sizeof(char *) * expander_count(var) + 1, 0);
	while (*var)
	{
		new[j++] = add_expander_word(&var);
		if (*var)
			var++;
	}
	new[j] = 0;
	return (new);
}