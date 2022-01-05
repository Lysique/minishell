/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:09:00 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/05 16:48:13 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strequ(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_cd_exit_export(t_cmdline *cmdline)
{
	if (ft_strequ(cmdline->cmds->cmd, "exit"))
	{
		cmdline->exit = cmdline->builtins[0].fct(cmdline);
		return (1);
	}
	else if (ft_strequ(cmdline->cmds->cmd, "cd"))
	{
		cmdline->exit = cmdline->builtins[1].fct(cmdline);
		return (1);
	}
	else if (ft_strequ(cmdline->cmds->cmd, "export"))
	{
		cmdline->exit = cmdline->builtins[5].fct(cmdline);
		return (1);
	}
	else if (ft_strequ(cmdline->cmds->cmd, "unset"))
	{
		cmdline->exit = cmdline->builtins[6].fct(cmdline);
		return (1);
	}
	return (0);
}

int	check_if_builtin(t_cmdline *cmdline, t_builtins *builtins)
{
	int		i;
	t_cmds	cmds;

	i = 0;
	cmds = *cmdline->cmds;
	while (builtins[i].builtin)
	{
		if (ft_strequ(builtins[i].builtin, cmds.cmd))
		{
			builtins[i].fct(cmdline);
			return (1);
		}
		i++;
	}
	return (0);
}
