/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:47:11 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/20 13:44:39 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child_handler(t_cmdline *cl, int sig)
{
	if (!kill(cl->is_forked, sig))
	{
		if (sig == SIGINT)
		{
			ft_printf("\n");
			cl->exit = 130;
		}
		if (sig == SIGQUIT)
		{
			ft_printf("\n");
			cl->exit = 131;
		}
	}
	else if (sig == SIGINT)
	{
		ft_printf("\n");
		cl->exit = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		cl->quit = 1;
	}
}

void	sig_handler(int sig, siginfo_t *siginfo, void *uac)
{
	t_cmdline	*cl;

	(void) uac;
	(void) siginfo;
	cl = cl_ptr(NULL);
	if ((sig == SIGINT || sig == SIGQUIT) && cl->is_forked)
		child_handler(cl, sig);
	else
	{
		if (sig == SIGINT)
		{
			ft_printf("\n");
			cl->exit = 1;
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			cl->quit = 1;
		}
		if (sig == SIGQUIT)
		{
			ft_printf("%s%s", cl->prompt, rl_line_buffer);
			rl_redisplay();
			cl->quit = 2;
		}
	}
}

void	setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	reset_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	signal_management(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sigaction));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	setup_term();
}