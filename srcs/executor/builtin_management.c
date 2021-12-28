/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:09:00 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/28 14:22:58 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
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

int	is_cd_or_exit(t_cmdline *cmdline)
{
	if (ft_strcmp(cmdline->cmds->cmd, "exit"))
	{
		cmdline->builtins[0].fct(cmdline);
		return (1);
	}
	else if (ft_strcmp(cmdline->cmds->cmd, "cd"))
	{
		cmdline->builtins[1].fct(cmdline);
		return (1);
	}
	else if (ft_strcmp(cmdline->cmds->cmd, "export"))
	{
		cmdline->builtins[5].fct(cmdline);
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
		if (ft_strcmp(builtins[i].builtin, cmds.cmd))
		{
			builtins[i].fct(cmdline);
			return (1);
		}
		i++;
	}
	return (0);
}
