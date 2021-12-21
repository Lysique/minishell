/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:13:45 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/13 16:52:19 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*builtin_name(char *builtin)
{
	int		i;
	char	*new;

	i = 0;
	while (builtin[i])
		i++;
	new = ft_malloc(i + 1, 0);
	i = 0;
	while (builtin[i])
	{
		new[i] = builtin[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

t_builtins	*builtins_init(void)
{
	t_builtins	*builtins;

	builtins = ft_malloc(sizeof(t_builtins) * 4, 0);
	builtins[0].builtin = builtin_name("exit");
	builtins[0].fct = ft_exit;
	builtins[1].builtin = builtin_name("echo");
	builtins[1].fct = ft_echo;
	builtins[2].builtin = builtin_name("pwd");
	builtins[2].fct = ft_pwd;
	builtins[3].builtin = builtin_name("cd");
	builtins[3].fct = ft_cd;
	builtins[4].builtin = 0;
	return (builtins);
}

void	executor(t_cmdline *cmdline)
{
	int			i;
	t_builtins	*builtins;

	i = 0;
	(void)cmdline;
	builtins = builtins_init();
//	while (cmdline->cmds[i].command)
//		printf("Command : %s\n", cmdline->cmds[i++].command);
//	pipex(cmdline->cmds, builtins);
	ft_printf("/\\ execution done \\\n");
}
