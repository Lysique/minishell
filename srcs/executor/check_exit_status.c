/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 12:46:07 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/20 12:59:42 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_exit_status(t_cmdline *cmdline)
{
	int		parentheses;
	t_cmds	*cmds;
	int		pipe;

	cmds = cmdline->cmds;
	if (!cmdline->exit)
		cmdline->exit = WEXITSTATUS(cmds->exitstatus);
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
}
