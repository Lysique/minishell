/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:18:28 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/27 18:16:31 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*split_cmd_to_args(char *cmd, t_cmdline *cmdline)
{
	char	**arr;
	int		i;
	t_args	*tmp;
	t_args	*tmp2;
	t_args	*tmp3;

	arr = expander_split(cmd);
	i = 1;
	while (arr[i])
	{
		tmp = ft_malloc(sizeof(t_args), 0);
		tmp->next = cmdline->cmds->args;
		tmp->content = arr[i];
		if (i++ == 1)
			tmp3 = tmp;
		else
			tmp2->next = tmp;
		tmp2 = tmp;
	}
	if (i != 1)
		cmdline->cmds->args = tmp3;
	return (arr[0]);
}

char	*split_content_to_args(char *content, t_cmdline *cmdline)
{
	char	**arr;
	int		i;
	t_args	*tmp;
	t_args	*tmp2;

	arr = expander_split(content);
	tmp = cmdline->cmds->args;
	i = 1;
	while (arr[i])
	{
		tmp2 = ft_malloc(sizeof(t_args), 0);
		tmp2->next = tmp->next;
		tmp->next = tmp2;
		tmp = tmp->next;
		tmp2->content = arr[i];
		tmp2 = tmp2->next;
		i++;
	}
	return (arr[0]);
}

char	*expand(char *var, t_cmdline *cmdline)
{
	int	i;
	int	double_quote;

	i = -1;
	double_quote = -1;
	while (var[++i])
	{
		if (var[i] == 39 && double_quote == -1 && ++i)
			while (var[i] && var[i] != 39)
				i++;
		if (var[i] == 34)
			double_quote = double_quote * -1;
		if (var[i] == '$' && var[i + 1] && var[i + 1] != 34
			&& var[i + 1] != 39)
			var = expand_dollar(var, cmdline, i);
	}
	return (var);
}

void	expander(t_cmdline *cmdline)
{
	t_args	*tmp;

	tmp = cmdline->cmds->args;
	cmdline->cmds->cmd = expand(cmdline->cmds->cmd, cmdline);
	cmdline->cmds->cmd = expand_wildcard(cmdline->cmds->cmd);
	cmdline->cmds->cmd = split_cmd_to_args(cmdline->cmds->cmd, cmdline);
	while (tmp)
	{
		tmp->content = expand(tmp->content, cmdline);
		tmp->content = expand_wildcard(tmp->content);
		tmp->content = split_content_to_args(tmp->content, cmdline);
		tmp = tmp->next;
	}
}
