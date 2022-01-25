/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_piped_conditional.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:38:37 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/25 15:01:06 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_piped_conditional(t_cmdline *cmdline)
{
	t_cmds	*current;
	int		parentheses;

	if (cmdline->cmds->pipetype <= 1 || cmdline->cmds->parentheses <= 0)
		return (0);
	current = cmdline->cmds;
	current++;
	parentheses = current->parentheses;
	while (current->command)
	{
		if (parentheses < 0 && current->pipetype == 1)
			return (1);
		current++;
		parentheses += current->parentheses;
	}
	return (0);
}
