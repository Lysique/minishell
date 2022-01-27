/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:04:52 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/27 18:16:28 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_quote(char *var, int i, int quote)
{
	i++;
	while (var[i] != quote && var[i])
		i++;
	return (i);
}

int	expander_count(char *var)
{
	int	i;
	int	nb;

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
			i = skip_quote(var, i, var[i]);
		if (var[i])
			i++;
	}
	return (nb);
}

int	ft_countlength(char *var)
{
	int	i;

	i = 0;
	while (!ft_isspace(var[i]) && var[i])
	{
		if (var[i] == 39 || var[i] == 34)
			i = skip_quote(var, i, var[i]);
		if (var[i])
			i++;
	}
	return (i);
}

char	*add_expander_word(char *var, int *i)
{
	char	*new;
	int		quote;
	int		j;

	new = ft_malloc(ft_countlength(var) + 1, 0);
	j = 0;
	while (!ft_isspace(var[*i]) && var[*i])
	{
		if (var[*i] == 39 || var[*i] == 34)
		{
			quote = var[(*i)++];
			while (var[*i] && var[*i] != quote)
				new[j++] = var[(*i)++];
			if (var[*i])
				*i += 1;
			continue ;
		}
		if (var[*i])
			new[j++] = var[(*i)++];
	}
	new[j] = '\0';
	return (new);
}

char	**expander_split(char *var)
{
	int		j;
	int		i;
	char	**new;

	j = 0;
	i = 0;
	new = ft_malloc(sizeof(char *) * (expander_count(var) + 1), 0);
	if (!var[i])
		new[j++] = add_expander_word(var, &i);
	while (var[i])
	{
		new[j++] = add_expander_word(var, &i);
		if (var[i])
			i++;
		while (ft_isspace(var[i]))
			i++;
	}
	new[j] = 0;
	return (new);
}
