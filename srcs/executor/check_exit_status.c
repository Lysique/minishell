/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 12:46:07 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/25 13:17:41 by slathouw         ###   ########.fr       */
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

void	check_exit_status(t_cmdline *cmdline, t_cmds **currentptr)
{
	int		parentheses;
	t_cmds	*cmds;
	int		pipe;

	cmds = cmdline->cmds;
	if (!cmdline->exit)
		set_exit_status(cmdline);
	if ((cmds->pipetype == 3 && cmdline->exit)
		|| (cmds->pipetype == 2 && cmdline->exit == 0))
	{
		pipe = cmds->pipetype;
		cmdline->cmds++;
		parentheses = cmdline->cmds->parentheses;
		while (parentheses || cmdline->cmds->pipetype == pipe)
		{
			cmdline->cmds++;
			parentheses += cmdline->cmds->parentheses;
		}
	}
	*currentptr = cmdline->cmds;
}
