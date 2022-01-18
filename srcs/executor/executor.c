/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:06:56 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/18 09:12:02 by slathouw         ###   ########.fr       */
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

void	builtins_init(t_cmdline *cmdline)
{
	cmdline->builtins[0].builtin = builtin_name("exit");
	cmdline->builtins[0].fct = ft_exit;
	cmdline->builtins[1].builtin = builtin_name("cd");
	cmdline->builtins[1].fct = ft_cd;
	cmdline->builtins[2].builtin = builtin_name("pwd");
	cmdline->builtins[2].fct = ft_pwd;
	cmdline->builtins[3].builtin = builtin_name("echo");
	cmdline->builtins[3].fct = ft_echo;
	cmdline->builtins[4].builtin = builtin_name("env");
	cmdline->builtins[4].fct = ft_env;
	cmdline->builtins[5].builtin = builtin_name("export");
	cmdline->builtins[5].fct = ft_export;
	cmdline->builtins[6].builtin = builtin_name("unset");
	cmdline->builtins[6].fct = ft_unset;
	cmdline->builtins[7].builtin = 0;
}

void	executor(t_cmdline *cmdline)
{
	t_builtins	builtins[8];

	cmdline->builtins = builtins;
	builtins_init(cmdline);
	pipex(cmdline);
}
