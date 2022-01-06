/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscarriage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 10:03:25 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/06 11:22:36 by tamighi          ###   ########.fr       */
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
	expander(cmdline);
	if (is_last_child(cmdline) && check_if_builtin(cmdline, cmdline->builtins))
		return (1);
	return (0);
}

