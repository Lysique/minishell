/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:06:56 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/23 10:44:25 by slathouw         ###   ########.fr       */
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

	builtins = ft_malloc(sizeof(t_builtins) * 5, 0);
	builtins[0].builtin = builtin_name("exit");
	builtins[0].fct = ft_exit;
	builtins[1].builtin = builtin_name("echo");
	builtins[1].fct = ft_echo;
	builtins[2].builtin = builtin_name("pwd");
	builtins[2].fct = ft_pwd;
	builtins[3].builtin = builtin_name("cd");
	builtins[3].fct = ft_cd;
	builtins[4].builtin = builtin_name("env");
	builtins[4].fct = ft_env;
	builtins[5].builtin = 0;
	return (builtins);
}

int	ft_srch(char *envp)
{
	int		i;
	int		j;
	char	*path;

	path = "PATH=";
	i = 0;
	j = 4;
	while (i <= j)
	{
		if (envp[i] != path[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_check(char s1, char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

void	executor(t_cmdline *cmdline)
{
	t_builtins	*builtins;

	builtins = builtins_init();
	cmdline->builtins = builtins;
	pipex(cmdline);
	ft_printf(BGRN "/\\ execution done \\\n" RESET);
}
