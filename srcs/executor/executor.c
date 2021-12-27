/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:06:56 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/27 11:14:44 by slathouw         ###   ########.fr       */
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
//TODO: FIX builtins to include env AND put them on STACK instead of HEAP
t_builtins	*builtins_init(void)
{
	t_builtins	*builtins;

	builtins = ft_malloc(sizeof(t_builtins) * 7, 0);
	builtins[0].builtin = builtin_name("exit");
	builtins[0].fct = ft_exit;
	builtins[1].builtin = builtin_name("cd");
	builtins[1].fct = ft_cd;
	builtins[2].builtin = builtin_name("pwd");
	builtins[2].fct = ft_pwd;
	builtins[3].builtin = builtin_name("echo");
	builtins[3].fct = ft_echo;
	builtins[4].builtin = builtin_name("env");
	builtins[4].fct = ft_env;
	builtins[5].builtin = builtin_name("export");
	builtins[5].fct = ft_export;
	builtins[6].builtin = 0;
	return (builtins);
}

void	executor(t_cmdline *cmdline)
{
	cmdline->builtins = builtins_init();
	pipex(cmdline);
	ft_printf(BGRN "/\\ execution done \\\n" RESET);
}
