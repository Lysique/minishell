/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 08:30:13 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/31 13:00:49 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt(t_cmdline *cmdline)
{
	if (cmdline->exit == 0)
		ft_printf(BMAG "🤪 minishell 👉 " RESET);
	else
		ft_printf(BRED "%i?>" BMAG "🤪 minishell 👉 " RESET, cmdline->exit);
}

t_cmdline	*cl_ptr(t_cmdline *cl)
{
	static t_cmdline	*cmdl;

	if (!cmdl)
		cmdl = cl;
	return (cmdl);
}

void	execute_minishell(char **env)
{
	char		**arr;
	t_cmdline	cmdline;

	ft_bzero(&cmdline, sizeof(t_cmdline));
	env_init(env, &cmdline);
	env_set(&cmdline, "SHLVL", "2");
	cmdline.shellpid = getpid();
	cl_ptr(&cmdline);
	while (1)
	{
//		signal_management();
		if (cmdline.quit == 0)
			prompt(&cmdline);
		cmdline.line = readline(NULL);
		if (!cmdline.line)
			exit(cmdline.exit);
		if (!*cmdline.line)
		{
			ft_printf("\n");
			free(cmdline.line);
			cmdline.line = NULL;
			cmdline.quit = 0;
			continue ;
		}
		add_history(cmdline.line);
		arr = lexer(cmdline.line);
		if (check_cmdline(arr))
		{
			printf("minishell : syntax error near token '%s'\n", check_cmdline(arr));
			ft_malloc(-2, 0);
			continue ;
		}
		parser(arr, &cmdline);
		expander(&cmdline);
		executor(&cmdline);
		printf("EXIT : %d\n", cmdline.exit);
		cmdline.quit = 0;
		ft_malloc(-2, 0);
	}
}
