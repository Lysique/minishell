/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_in_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:03:06 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/31 15:14:36 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*arg_line(char **line)
{
	char	*new;
	int		i;

	i = 0;
	while ((*line)[i] && (*line)[i] != ' ' && (*line)[i] != '|'
		&& (*line)[i] != '&' && (*line)[i] != '<' && (*line)[i] != '>'
		&& (*line)[i] != '(' && (*line)[i] != ')')
		i++;
	new = ft_malloc(i + 1, 0);
	i = 0;
	while (**line && **line != ' ' && **line != '|' && **line != '&'
		&& **line != '<' && **line != '>' && **line != '('
		&& **line != ')')
	{
		new[i++] = **line;
		(*line)++;
	}
	new[i] = '\0';
	while (**line == ' ')
		(*line)++;
	return (new);
}

char	*parentheses_line(char **line)
{
	char	*new;

	new = ft_malloc(2, 0);
	new[0] = **line;
	(*line)++;
	new[1] = 0;
	while (**line == ' ')
		(*line)++;
	return (new);
}

char	*pipe_redir_line(char **line)
{
	char	pipe;
	int		i;
	char	*new;

	i = 0;
	pipe = **line;
	while ((*line)[i] == pipe)
		i++;
	new = ft_malloc(i + 1, 0);
	i = 0;
	while (**line == pipe)
	{
		new[i++] = **line;
		(*line)++;
	}
	new[i] = '\0';
	while (**line == ' ')
		(*line)++;
	return (new);
}

char	*quote_line(char **line)
{
	int		i;
	char	quote;
	char	*new;

	i = 0;
	quote = **line;
	(*line)++;
	while ((*line)[i] != quote && (*line)[i])
		i++;
	new = ft_malloc(i + 3, 0);
	i = 0;
	new[i++] = quote;
	while (**line != quote && **line)
	{
		new[i++] = **line;
		(*line)++;
	}
	new[i++] = **line;
	new[i] = '\0';
	(*line)++;
	while (**line == ' ')
		(*line)++;
	return (new);
}

char	**tokens_in_arr(char *line, char **arr)
{
	int	j;

	j = 0;
	while (*line == ' ')
		line++;
	while (*line)
	{
		if (*line == 34 || *line == 39)
			arr[j] = quote_line(&line);
		else if (*line == '|' || *line == '&' || *line == '<' || *line == '>')
			arr[j] = pipe_redir_line(&line);
		else if (*line == '(' || *line == ')')
			arr[j] = parentheses_line(&line);
		else
			arr[j] = arg_line(&line);
		j++;
	}
	arr[j] = 0;
	return (arr);
}
