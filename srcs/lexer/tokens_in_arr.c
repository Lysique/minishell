/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_in_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:03:06 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/05 13:17:47 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*parentheses_line(char **line)
{
	char	*new;

	new = ft_malloc(2, 0);
	new[0] = **line;
	(*line)++;
	new[1] = 0;
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
	return (new);
}

int	nb_char_arg(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '|'
		&& line[i] != '&' && line[i] != '<' && line[i] != '>'
		&& line[i] != '(' && line[i] != ')')
	{
		if (line[i] == 39 || line[i] == 34)
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
		}
		if (line[i])
			i++;
	}
	return (i);
}

char	*arg_line(char **line)
{
	char	*new;
	int		i;
	char	quote;

	i = 0;
	new = ft_malloc(nb_char_arg(*line) + 1, 0);
	while (**line && **line != ' ' && **line != '|' && **line != '&'
		&& **line != '<' && **line != '>' && **line != '('
		&& **line != ')')
	{
		if (**line == 39 || **line == 34)
		{
			quote = **line;
			new[i++] = **line;
			while (++(*line) && **line != quote)
				new[i++] = **line;
		}
		new[i++] = **line;
		(*line)++;
	}
	new[i] = '\0';
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
		if (*line == '|' || *line == '&' || *line == '<' || *line == '>')
			arr[j] = pipe_redir_line(&line);
		else if (*line == '(' || *line == ')')
			arr[j] = parentheses_line(&line);
		else
			arr[j] = arg_line(&line);
		while (*line == ' ')
			line++;
		//printf("ARR[%d] = %s|\n", j, arr[j]);
		j++;
	}
	arr[j] = 0;
	return (arr);
}
