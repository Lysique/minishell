/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:04:02 by tamighi           #+#    #+#             */
/*   Updated: 2021/11/22 14:56:57 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
