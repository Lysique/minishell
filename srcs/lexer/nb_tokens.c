/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:50:40 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/29 15:33:37 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_parentheses(char *line)
{
	line++;
	return (line);
}

static char	*handle_pipe_redir(char *line)
{
	char	redir_or_pipe;

	redir_or_pipe = *line;
	while (*line == redir_or_pipe)
		line++;
	return (line);
}

static char	*handle_quotes(char *line)
{
	char	quote;

	quote = *line;
	line++;
	while (*line != quote && *line)
		line++;
	if (*line == quote)
		line++;
	return (line);
}

static char	*handle_arg(char *line)
{
	while (*line && !ft_isspace(*line) && *line != '|' && *line != '&'
		&& *line != '<' && *line != '>' && *line != '('
		&& *line != ')')
	{
		if (*line == 34 || *line == 39)
			line = handle_quotes(line);
		else
			line++;
	}
	return (line);
}

int	nb_tokens(char *line)
{
	int	count;

	count = 0;
	while (ft_isspace(*line))
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
		while (ft_isspace(*line))
			line++;
		count++;
	}
	return (count);
}
