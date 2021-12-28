/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:05:39 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/28 17:08:16 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_process(t_cmdline *cmdline)
{
	int		p;

	wait(&cmdline->cmds->exitstatus);
	check_exit_status(&cmdline->cmds);
	if (close(cmdline->cmds->p[1]) == -1)
		exit(EXIT_FAILURE);
	p = cmdline->cmds->p[0];
	cmdline->cmds++;
	cmdline->cmds->fd_in = p;
}

void	pipex(t_cmdline *cmdline)
{
	pid_t	pid;

	cmdline->cmds->fd_in = 0;
	while (cmdline->cmds->command != NULL)
	{
		pipe(cmdline->cmds->p);
		if (is_cd_exit_export(cmdline))
		{
			cmdline->cmds++;
			continue ;
		}
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			if ((cmdline->cmds + 1)->command != NULL && cmdline->cmds->pipetype == 1)
				dup2(cmdline->cmds->p[1], 1);
			if (close(cmdline->cmds->p[0]) == -1)
				exit(EXIT_FAILURE);
			if (!check_if_builtin(cmdline, cmdline->builtins))
				redir_exec(cmdline);
			exit(0);
		}
		else
			parent_process(cmdline);
	}
}
