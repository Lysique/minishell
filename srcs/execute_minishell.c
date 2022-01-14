/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 08:30:13 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/14 13:23:59 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
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

void	execute_minishell(char **env)
{
	char		**arr;
	t_cmdline	cmdline;

	ft_bzero(&cmdline, sizeof(t_cmdline));
	env_init(env, &cmdline);
	env_set(&cmdline, "SHLVL", "2");
	cmdline.shellpid = getpid();
	cl_ptr(&cmdline);
	signal_management();
	while (1)
	{
		prompt(&cmdline);
		cmdline.line = readline(cmdline.prompt);
		if (!cmdline.line)
		{
			ft_printf("\bexit");
			free_env(cmdline.env);
			ft_ptrdel(cmdline.prompt);
			ft_malloc(-2, 0);
			exit(0);
		}
		if (!*cmdline.line)
		{
			ft_ptrdel(cmdline.line);
			cmdline.quit = 0;
			continue ;
		}
		add_history(cmdline.line);
		arr = lexer(cmdline.line);
		if (!*arr)
		{
			ft_ptrdel(cmdline.line);
			continue ;
		}
		if (check_cmdline(arr))
		{
			ft_fdprintf(2,
				"minishell : syntax error near unexpected token '%s'\n",
				check_cmdline(arr));
			cmdline.exit = EXIT_SYNTAX_ERR;
			ft_ptrdel(cmdline.line);
			ft_malloc(-2, 0);
			continue ;
		}
		parser(arr, &cmdline);
		executor(&cmdline);
//		printf("EXIT : %d\n", cmdline.exit);
		ft_ptrdel(cmdline.line);
		cmdline.quit = 0;
		ft_malloc(-2, 0);
	}
}
