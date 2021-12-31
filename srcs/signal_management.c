/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:47:11 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/31 16:45:05 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

void	sig_handler(int sig, siginfo_t *siginfo, void *uac)
{
	t_cmdline	*cl;

	(void) uac;
	cl = cl_ptr(NULL);
	if (sig == SIGINT)
	{
		ft_printf(BMAG "🤪 minishell 👉   \b\b\n" RESET);
		if (cl->shellpid == siginfo->si_pid)
		{
			cl->exit = 130;
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			cl->quit = 1;
		}
		else
			cl->exit = 1;
	}
	if (sig == SIGQUIT)
	{
		ft_printf("\b\b  ");
		ft_printf("exit\n");
		cl->quit = 2;
	}
}

void	signal_management()
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
