/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscarriage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 10:03:25 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/25 13:23:07 by slathouw         ###   ########.fr       */
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
