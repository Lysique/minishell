/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 08:30:13 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/20 15:36:40 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exit_if_null_line(t_cmdline *cmdline)
{
	if (!cmdline->line)
	{
		ft_printf("\bexit");
		free_env(cmdline->env);
		ft_ptrdel(cmdline->prompt);
		ft_malloc(-2, 0);
		exit(0);
	}
}

static int	check_syntax_error(t_cmdline *cmdline, char **arr)
{
	if (check_cmdline(arr))
	{
		ft_fdprintf(2,
			"minishell : syntax error near unexpected token '%s'\n",
			check_cmdline(arr));
		cmdline->exit = EXIT_SYNTAX_ERR;
		ft_ptrdel(cmdline->line);
		ft_malloc(-2, 0);
		return (1);
	}
	return (0);
}

static int	arr_is_empty(t_cmdline *cmdline, char **arr)
{
	if (!*arr)
	{
		ft_ptrdel(cmdline->line);
		return (1);
	}
	return (0);
}

static int	empty_line(t_cmdline *cmdline)
{
	if (!*(cmdline->line))
	{
		ft_ptrdel(cmdline->line);
		cmdline->quit = 0;
		return (1);
	}
	return (0);
}

void	execute_minishell(char **env)
{
	char		**arr;
	t_cmdline	cmdline;

	minishell_init(&cmdline, env);
	while (1)
	{
		signal_management();
		prompt(&cmdline);
		cmdline.line = readline(cmdline.prompt);
		exit_if_null_line(&cmdline);
		if (empty_line(&cmdline))
			continue ;
		add_history(cmdline.line);
		arr = lexer(cmdline.line);
		if (arr_is_empty(&cmdline, arr))
			continue ;
		if (check_syntax_error(&cmdline, arr))
			continue ;
		parser(arr, &cmdline);
		executor(&cmdline);
		ft_ptrdel(cmdline.line);
		cmdline.quit = 0;
		ft_malloc(-2, 0);
	}
}
