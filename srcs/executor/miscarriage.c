/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscarriage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 10:03:25 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/06 16:35:09 by tamighi          ###   ########.fr       */
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

