/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 10:20:52 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/06 18:02:12 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_process(t_cmdline *cmdline)
{
	int		p;

	if (cmdline->cmds->pipetype != 1)
	{
		while (wait(&cmdline->cmds->exitstatus) != -1)
			;
		check_exit_status(cmdline);
	}
	if (!cmdline->cmds->cmd)
		return ;
	if (cmdline->cmds->p[0] != 0 && close(cmdline->cmds->p[1]) == -1)
		exit(EXIT_FAILURE);
	p = cmdline->cmds->p[0];
	cmdline->cmds++;
	cmdline->cmds->fd_in = p;
}

void	fork_call(t_cmdline *cmdline)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE); //correct exit
	else if (pid == 0)
	{
		if (close(cmdline->cmds->p[0]) == -1)
			exit(EXIT_FAILURE);
		if ((cmdline->cmds + 1)->command && cmdline->cmds->pipetype == 1)
			dup2(cmdline->cmds->p[1], 1);
		if (!check_if_builtin(cmdline, cmdline->builtins))
			redir_exec(cmdline);
		exit(0);
	}
	else
		parent_process(cmdline);
}

void	pipex(t_cmdline *cmdline)
{
	cmdline->cmds->fd_in = 0;
	expander(cmdline);
	pipe(cmdline->cmds->p);
	if (miscarriage(cmdline))
	{
		cmdline->cmds->exitok = 1;
		check_exit_status(cmdline);
		if (cmdline->cmds->cmd)
			cmdline->cmds++;
		if (cmdline->cmds->cmd)
			pipex(cmdline);
		return ;	
	}
	else
		fork_call(cmdline);
	while (cmdline->cmds->command && (cmdline->cmds - 1)->pipetype <= 1)
	{
		pipe(cmdline->cmds->p);
		expander(cmdline);
		fork_call(cmdline);
	}
	if (cmdline->cmds->cmd)
		pipex(cmdline);
}
