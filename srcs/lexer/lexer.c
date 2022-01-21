/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:04:02 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/21 08:00:50 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '	')
		return (1);
	return (0);
}

static char	**create_token_arr(char *line)
{
	char	**arr;
	int		tokens;

	tokens = nb_tokens(line);
	arr = ft_malloc(sizeof(char *) * (tokens + 1), 0);
	ft_bzero(arr, sizeof(char *) * (tokens + 1));
	arr = tokens_in_arr(line, arr);
	return (arr);
}

char	**lexer(char *line)
{
	char	**tokens;

	tokens = create_token_arr(line);
	return (tokens);
}
