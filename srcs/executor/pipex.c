/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 10:20:52 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/18 11:02:37 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_process(t_cmdline *cmdline)
{
	int		p;

	cmdline->is_forked = 1;
	if (close(cmdline->cmds->p[1]) == -1)
		exit(EXIT_FAILURE);
	if (cmdline->cmds->pipetype != 1)
	{
		while (wait(&cmdline->cmds->exitstatus) != -1)
			;
		check_exit_status(cmdline);
	}
	if (!cmdline->cmds->cmd)
		return ;
	p = cmdline->cmds->p[0];
	cmdline->cmds++;
	cmdline->cmds->fd_in = p;
	cmdline->is_forked = 0;
}

void	fork_call(t_cmdline *cmdline)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		if (close(cmdline->cmds->p[0]) == -1)
			exit(EXIT_FAILURE);
		if ((cmdline->cmds + 1)->command && cmdline->cmds->pipetype == 1
			&& !cmdline->cmds->outfiles)
			dup2(cmdline->cmds->p[1], 1);
		if (cmdline->cmds->outfiles)
			dup2(cmdline->cmds->outfiles->fd, 1);
		if (!check_if_builtin(cmdline, cmdline->builtins))
			redir_exec(cmdline);
		exit(0);
	}
	else
		parent_process(cmdline);
}

static void	set_fds(t_cmdline *cmdline)
{
	if (cmdline->cmds->infiles)
		cmdline->cmds->fd_in = cmdline->cmds->infiles->fd;
	if (cmdline->cmds->outfiles)
		cmdline->cmds->fd_out = cmdline->cmds->outfiles->fd;
}

void	pipex(t_cmdline *cmdline)
{
	set_fds(cmdline);
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
