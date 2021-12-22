/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 12:46:07 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/22 13:49:35 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_exit_status(t_cmds **cmds)
{
	int	parentheses;

	parentheses = (*cmds)->parentheses;
	if ((WEXITSTATUS((*cmds)->exitstatus) == 1 && ((*cmds)->pipetype == 3))
		|| (WEXITSTATUS((*cmds)->exitstatus) == 0 && ((*cmds)->pipetype == 2)))
	{
		(*cmds)++;
		parentheses += (*cmds)->parentheses;
		while (parentheses)
		{
			(*cmds)++;
			parentheses += (*cmds)->parentheses;
		}
	}
}
