/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:50:40 by tamighi           #+#    #+#             */
/*   Updated: 2021/11/22 14:29:18 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_arg(char *line)
{
	while (*line && *line != ' ' && *line != '|' && *line != '&'
		&& *line != '<' && *line != '>' && *line != '('
		&& *line != ')')
		line++;
	while (*line == ' ')
		line++;
	return (line);
}

char	*handle_parentheses(char *line)
{
	line++;
	while (*line == ' ')
		line++;
	return (line);
}

char	*handle_pipe_redir(char *line)
{
	char	redir_or_pipe;

	redir_or_pipe = *line;
	while (*line == redir_or_pipe)
		line++;
	while (*line == ' ')
		line++;
	return (line);
}

char	*handle_quotes(char *line)
{
	char	quote;

	quote = *line;
	line++;
	while (*line != quote && *line)
		line++;
	if (*line == quote)
		line++;
	while (*line == ' ')
		line++;
	return (line);
}

int	nb_tokens(char *line)
{
	int	count;

	count = 0;
	while (*line == ' ')
		line++;
	if (!*line)
		return (0);
	while (*line)
	{
		if (*line == 34 || *line == 39)
			line = handle_quotes(line);
		else if (*line == '|' || *line == '&' || *line == '<' || *line == '>')
			line = handle_pipe_redir(line);
		else if (*line == '(' || *line == ')')
			line = handle_parentheses(line);
		else
			line = handle_arg(line);
		count++;
	}
	return (count);
}
