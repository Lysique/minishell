/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:09:00 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/06 10:02:21 by tamighi          ###   ########.fr       */
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
