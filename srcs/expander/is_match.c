/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:41:40 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/18 09:26:58 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	**get_2d_arr(int x, int y)
{
	int	**arr;
	int	i;

	arr = ft_calloc(x, sizeof(int *));
	i = -1;
	while (++i < x)
		arr[i] = ft_calloc(y, sizeof(int));
	return (arr);
}

static void	free_2d_arr(void *arr, int y)
{
	int	**to_free;
	int	i;

	to_free = (int **) arr;
	i = -1;
	if (to_free)
	{
		while (++i < y)
			if (to_free[i])
				free(to_free[i]);
		free(to_free);
	}
}

static void	init_empty_word(char *pattern, int **lookup)
{
	const int	pl = ft_strlen(pattern);
	int			j;

	lookup[0][0] = 1;
	j = 0;
	while (++j <= pl)
		if (pattern[j - 1] == '*')
			lookup[0][j] = lookup[0][j - 1];
}

int	is_match(char *word, char *pattern)
{
	int	wl;
	int	pl;
	int	**lookup;
	int	i;
	int	j;

	wl = ft_strlen(word);
	pl = ft_strlen(pattern);
	lookup = get_2d_arr(wl + 1, pl + 1);
	init_empty_word(pattern, lookup);
	i = 0;
	while (++i <= wl)
	{
		j = 0;
		while (++j <= pl)
		{
			if (pattern[j - 1] == '*')
				lookup[i][j] = (lookup[i - 1][j] || lookup[i][j - 1]);
			else if (pattern[j - 1] == '?' || word[i - 1] == pattern[j - 1])
				lookup[i][j] = lookup[i - 1][j - 1];
		}
	}
	j = lookup[wl][pl];
	free_2d_arr(lookup, wl + 1);
	return (j);
}

int	is_visible(char *name, char *pattern)
{
	if (name[0] == '.')
	{
		if (pattern[0] == '.')
			return (1);
		else
			return (0);
	}
	return (1);
}
