/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscarriage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 10:03:25 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/18 09:08:49 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_last_child(t_cmdline *cmdline)
{
	if (!(cmdline->cmds + 1)->command || cmdline->cmds->pipetype != 1)
		return (1);
	return (0);
}

int	miscarriage(t_cmdline *cmdline)
{
	if (!cmdline->cmds->command)
		return (0);
	if (is_last_child(cmdline) && check_if_builtin(cmdline, cmdline->builtins))
		return (1);
	return (0);
}
