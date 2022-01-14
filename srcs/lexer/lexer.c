/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:04:02 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/06 15:52:57 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '	')
		return (1);
	return (0);
}

char	**create_token_arr(char *line)
{
	char	**arr;
	int		tokens;

	tokens = nb_tokens(line);
	arr = ft_malloc(sizeof(char *) * (tokens + 1), 0);
	arr = tokens_in_arr(line, arr);
	return (arr);
}

char	**lexer(char *line)
{
	char	**tokens;

	tokens = create_token_arr(line);
	return (tokens);
}
