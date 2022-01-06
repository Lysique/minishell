/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 12:46:07 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/06 17:51:26 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_exit_status(t_cmdline *cmdline)
{
	int		parentheses;
	t_cmds	*cmds;

	cmds = cmdline->cmds;
	parentheses = cmds->parentheses;
	cmdline->exit = WEXITSTATUS(cmds->exitstatus);
	if ((cmds->pipetype == 3 && cmdline->exit)
		|| (cmds->pipetype == 2 && cmdline->exit == 0))
	{
		cmdline->cmds++;
		while (parentheses)
		{
			parentheses += cmdline->cmds->parentheses;
			cmdline->cmds++;
		}
	}
}
