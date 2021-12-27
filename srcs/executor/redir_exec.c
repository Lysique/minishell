/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:11:29 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/26 13:01:49 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_exec(t_cmdline *cmdline)
{
	char	**act;
	char	*path;
	t_cmds	*cmds;

	dup2(cmdline->cmds->fd_in, 0);
	cmds = cmdline->cmds;
	if ((*(cmds + 1)).command != NULL && cmds->pipetype == 1)
		dup2(cmdline->cmds->p[1], 1);
	if (close(cmdline->cmds->p[0]) == -1)
		exit(EXIT_FAILURE);
	act = ft_split(cmdline->cmds->command, ' ');
	path = find_path(act[0], cmdline->env);
	execve(path, act, cmdline->env);
	exit(EXIT_FAILURE);
}
