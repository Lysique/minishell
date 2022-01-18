/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:45:34 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/18 09:57:48 by slathouw         ###   ########.fr       */
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
	char	*tmp;
	char	*new_prompt;
	char	*exit_status;

	ft_ptrdel(cmdline->prompt);
	if (cmdline->exit == 0)
		cmdline->prompt = ft_strdup(BMAG "🤪 minishell 👉 " RESET);
	else
	{
		exit_status = ft_itoa(cmdline->exit);
		tmp = ft_strjoin(BRED, exit_status);
		ft_ptrdel(exit_status);
		new_prompt = ft_strjoin(tmp, "?>" BMAG "🤪 minishell 👉 " RESET);
		ft_ptrdel(tmp);
		cmdline->prompt = new_prompt;
	}
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
