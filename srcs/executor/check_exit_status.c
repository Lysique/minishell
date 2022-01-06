/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 12:46:07 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/06 11:45:42 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_exit_status(t_cmdline *cmdline)
{
	int		parentheses;
	t_cmds	*cmds;

	cmds = cmdline->cmds;
	parentheses = cmds->parentheses;
	if (((cmds - 1)->pipetype == 3 && WEXITSTATUS((cmds - 1)->exitstatus) == 1)
		|| ((cmds - 1)->pipetype == 2 && WEXITSTATUS((cmds - 1)->exitstatus) == 0))
	{
		cmdline->cmds++;
		while (parentheses)
		{
			parentheses += cmdline->cmds->parentheses;
			cmdline->cmds++;
		}
	}
	cmdline->exit = WEXITSTATUS((cmds - 1)->exitstatus);
}
