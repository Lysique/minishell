/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 08:30:13 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/03 14:09:19 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell.h"

void	prompt(t_cmdline *cmdline)
{
	char	*tmp;
	char	*new_prompt;
	char	*exit_status;

	if (cmdline->prompt)
		free(cmdline->prompt);
	if (cmdline->exit == 0)
		cmdline->prompt = ft_strdup(BMAG "🤪 minishell 👉 " RESET);
	else
	{
		exit_status = ft_itoa(cmdline->exit);
		tmp = ft_strjoin(BRED, exit_status);
		if (exit_status)
			free(exit_status);
		new_prompt = ft_strjoin(tmp, "?>" BMAG "🤪 minishell 👉 " RESET);
		if (tmp)
			free(tmp);
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
		signal_management();
		if (cmdline.quit == 0)
			prompt(&cmdline);
		cmdline.line = readline(cmdline.prompt);
		if (!cmdline.line)
			exit(cmdline.exit);
		if (!*cmdline.line)
		{
//			ft_printf("\n");
			free(cmdline.line);
			cmdline.line = NULL;
			cmdline.quit = 0;
			continue ;
		}
		add_history(cmdline.line);
		arr = lexer(cmdline.line);
		if (check_cmdline(arr))
		{
			printf("minishell : syntax error near token '%s'\n",
				check_cmdline(arr));
			ft_malloc(-2, 0);
			continue ;
		}
		parser(arr, &cmdline);
		executor(&cmdline);
		printf("EXIT : %d\n", cmdline.exit);
		cmdline.quit = 0;
		ft_malloc(-2, 0);
	}
}
