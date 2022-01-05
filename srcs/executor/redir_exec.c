/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:11:29 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/05 17:31:55 by ppizzo           ###   ########.fr       */
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
	if (!path)
	{
		cmdline->exit = 127;
		exit(EXIT_CMD_NOT_FOUND_ERR);
	}
	execve(path, act, cmdline->env);
}
