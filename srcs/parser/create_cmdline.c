/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmdline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 09:29:18 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/23 10:17:39 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmds	cmds_add_parentheses(char parentheses, t_cmds cmds)
{
	if (parentheses == '(')
		cmds.parentheses++;
	else if (parentheses == ')')
		cmds.parentheses--;
	return (cmds);
}

t_args	*arg_add(char *arg, t_cmds cmds)
{
	t_args	*new;
	t_args	*tmp;

	new = ft_malloc(sizeof(t_args), 0);
	new->content = arg;
	new->next = 0;
	if (!cmds.args)
		return (new);
	tmp = cmds.args;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (cmds.args);
}

t_cmds	cmds_add_cmd(char ***arr, t_cmds cmds)
{
	while (**arr)
	{
		if (***arr == '|' || ***arr == '&' || ***arr == '<' || ***arr == '>'
			|| ***arr == '(' || ***arr == ')')
			break ;
		if (!cmds.cmd)
			cmds.cmd = **arr;
		else
			cmds.args = arg_add(**arr, cmds);
		(*arr)++;
	}
	(*arr)--;
	return (cmds);
}

t_cmds	cmd_add_pipetype(char *arr, t_cmds cmds)
{
	if (arr[0] == '|' && arr[1])
		cmds.pipetype = 2;
	else if (arr[0] == '|')
		cmds.pipetype = 1;
	else
		cmds.pipetype = 3;
	return (cmds);
}

t_cmdline	*create_cmdline(char **arr, t_cmdline *cmdline)
{
	int	i;

	i = 0;
	while (*arr)
	{
		if (**arr == '|' || **arr == '&')
		{
			cmdline->cmds[i] = cmd_add_pipetype(*arr, cmdline->cmds[i]);
			i++;
		}
		else if (**arr == '(' || **arr == ')')
			cmdline->cmds[i] = cmds_add_parentheses(**arr, cmdline->cmds[i]);
		else if (**arr == '<' || **arr == '>')
		{
			cmdline->cmds[i] = cmds_add_lstfile(arr, cmdline->cmds[i]);
			arr++;
		}
		else
			cmdline->cmds[i] = cmds_add_cmd(&arr, cmdline->cmds[i]);
		arr++;
	}
	return (cmdline);
}
