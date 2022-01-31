/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_piped_conditional.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:38:37 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/31 12:54:43 by slathouw         ###   ########.fr       */
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

int	inf_outf_set(t_cmds *current, int *fds)
{
	if (current->infiles)
		dup2(current->infiles->fd, 0);
	if (current->outfiles)
		dup2(current->outfiles->fd, 1);
	if ((current->infiles && current->infiles->fd == -1)
		|| (current->outfiles && current->outfiles->fd == -1))
	{
		restore_stds(fds);
		switch_pipes_close_files(fds, current);
		return (0);
	}
	return (1);
}
