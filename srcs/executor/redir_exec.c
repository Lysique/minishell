/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:11:29 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/28 17:10:27 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_exec(t_cmdline *cmdline)
{
	char	**act;
	char	*path;

	dup2(cmdline->cmds->fd_in, 0);
	act = ft_split(cmdline->cmds->command, ' ');
	path = find_path(act[0], cmdline->env);
	execve(path, act, cmdline->env);
}
