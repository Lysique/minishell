/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:20:08 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/21 08:22:38 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*check_parentheses_count(char **arr)
{
	int	count;

	count = 0;
	while (*arr)
	{
		if (**arr == '(')
			count++;
		else if (**arr == ')')
			count--;
		if (count < 0)
			return (")");
		arr++;
	}
	if (count > 0)
		return ("(");
	else if (count < 0)
		return (")");
	return (0);
}

static char	*check_redir(char **arr)
{
	if (arr[0][1] && arr[0][2])
		return (*arr);
	arr++;
	if (!*arr)
		return ("newline");
	if (*arr && (**arr == '(' || **arr == ')' || **arr == '&' || **arr == '|'
			|| **arr == '<' || **arr == '>'))
		return (*arr);
	return (0);
}

static char	*check_pipe(char **arr)
{
	if (arr[0][0] == '&' && !(arr[0][1]))
		return (*arr);
	if (arr[0][1] && arr[0][2])
		return (*arr);
	arr++;
	if (!*arr)
		return ("newline");
	if (*arr && (**arr == '&' || **arr == '|' || **arr == ')'))
		return (*arr);
	return (0);
}

static char	*check_parentheses(char **arr)
{
	arr++;
	if (!*arr)
		return ("newline");
	if (**arr == '|' || **arr == '&')
		return (*arr);
	return (0);
}

char	*check_cmdline(char **arr)
{
	char	*checkptr;

	if (check_parentheses_count(arr))
		return (check_parentheses_count(arr));
	while (*arr)
	{
		checkptr = check_redir(arr);
		if ((**arr == '<' || **arr == '>') && checkptr)
			return (checkptr);
		checkptr = check_pipe(arr);
		if ((**arr == '|' || **arr == '&') && checkptr)
			return (checkptr);
		checkptr = check_parentheses(arr);
		if (**arr == '(' && checkptr)
			return (checkptr);
		if (*arr)
			arr++;
	}
	return (0);
}
