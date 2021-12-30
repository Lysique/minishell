/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 12:46:07 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/30 10:45:08 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_exit_status(t_cmdline *cmdline)
{
	int		parentheses;
	t_cmds	*cmds;

	cmds = cmdline->cmds;
	parentheses = cmds->parentheses;
	if ((WEXITSTATUS(cmds->exitstatus) == 1 && (cmds->pipetype == 3))
		|| (WEXITSTATUS(cmds->exitstatus) == 0 && (cmds->pipetype == 2)))
	{
		cmds++;
		parentheses += cmds->parentheses;
		while (parentheses)
		{
			cmds++;
			parentheses += cmds->parentheses;
		}
	}
	if (WEXITSTATUS(cmds->exitstatus) == 1)
		cmdline->exit = 1;
}
