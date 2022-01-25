/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscarriage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 10:03:25 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/25 12:51:40 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	miscarriage(t_cmdline *cmdline, int flag_in_out[2])
{
	if (!cmdline->cmds->command)
		return (0);
	cmdline->cmds->exitok = 1;
	if (!flag_in_out[0] && !flag_in_out[1]
		&& check_if_builtin(cmdline, cmdline->builtins))
		return (1);
	cmdline->cmds->exitok = 0;
	return (0);
}

int	pipe_continues(t_cmdline *cmdline, t_cmds *current)
{
	if ((current->pipetype == 2 && cmdline->exit == 0)
		|| (current->pipetype == 3 && cmdline->exit != 0))
		return (0);
	return (1);
}
