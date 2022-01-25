/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:45:34 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/25 15:31:35 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_ptrdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	prompt(t_cmdline *cmdline)
{
	ft_ptrdel(cmdline->prompt);
	cmdline->prompt = ft_strdup(BMAG "minishell 👉 " RESET);
}

t_cmdline	*cl_ptr(t_cmdline *cl)
{
	static t_cmdline	*cmdl;

	if (!cmdl)
		cmdl = cl;
	return (cmdl);
}

void	minishell_init(t_cmdline *cmdline, char **env)
{
	ft_bzero(cmdline, sizeof(t_cmdline));
	env_init(env, cmdline);
	shlvl_setter(cmdline);
	cmdline->shellpid = getpid();
	cl_ptr(cmdline);
	signal_management();
}
