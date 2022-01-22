/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:11:29 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/22 14:49:53 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**cmdline_to_arr(t_cmdline *cl)
{
	char	**arr;
	t_args	*currarg;
	int		count;
	int		i;

	arr = NULL;
	count = 1 + ft_lstsize(cl->cmds->args) + 1;
	arr = ft_malloc(sizeof(char *) * count, NULL);
	i = 0;
	arr[i] = cl->cmds->cmd;
	currarg = cl->cmds->args;
	while (++i < count - 1)
	{
		arr[i] = (char *)currarg->content;
		currarg = currarg->next;
	}
	arr[i] = 0;
	return (arr);
}

void	redir_exec(t_cmdline *cmdline)
{
	char	**act;
	char	*path;

	act = cmdline_to_arr(cmdline);
	path = find_path(act[0], cmdline->env);
	if (!path)
	{
		cmdline->exit = 127;
		exit(EXIT_CMD_NOT_FOUND_ERR);
	}
	execve(path, act, cmdline->env);
}
