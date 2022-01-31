/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 12:46:07 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/31 13:15:35 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_exit_status(t_cmdline *cl)
{
	t_cmds	*cmds;

	cmds = cl->cmds;
	if (WIFEXITED(cmds->exitstatus))
		cl->exit = WEXITSTATUS(cmds->exitstatus);
	if (WIFSIGNALED(cmds->exitstatus))
	{
		cl->exit = WTERMSIG(cmds->exitstatus);
		if (cl->exit != 131)
			cl->exit += 128;
	}
}

static void	close_files(t_cmds *cmd)
{
	while (cmd->outfiles && cmd->outfiles->fd > 2)
	{
		close(cmd->outfiles->fd);
		cmd->outfiles = cmd->outfiles->next;
	}
	while (cmd->infiles && cmd->infiles->fd > 2)
	{
		close(cmd->infiles->fd);
		cmd->infiles = cmd->infiles->next;
	}
}

void	check_exit_status(t_cmdline *cmdline, t_cmds **currentptr)
{
	int		parentheses;
	t_cmds	*cmds;
	int		pipe;

	cmds = cmdline->cmds;
	set_exit_status(cmdline);
	if ((cmds->pipetype == 3 && cmdline->exit)
		|| (cmds->pipetype == 2 && cmdline->exit == 0))
	{
		pipe = cmds->pipetype;
		close_files(cmdline->cmds);
		cmdline->cmds++;
		parentheses = cmdline->cmds->parentheses;
		while ((parentheses || cmdline->cmds->pipetype == pipe
				|| cmdline->cmds->pipetype == 1) && cmdline->cmds->command)
		{
			if (parentheses < 0)
				break ;
			close_files(cmdline->cmds);
			cmdline->cmds++;
			parentheses += cmdline->cmds->parentheses;
		}
	}
	*currentptr = cmdline->cmds;
}
