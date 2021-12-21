/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 08:30:13 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/14 13:49:59 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_minishell(char **env)
{
	char		**arr;
	char		*line;
	t_cmdline	*cmdline;

	signal_management();
	while (1)
	{
		line = readline("#minishell: ");
		add_history(line);
		if (!line)
			exit(0);
		arr = lexer(line);
		if (check_cmdline(arr))
		{
			printf("minishell : syntax error near token '%s'\n", check_cmdline(arr));
			ft_malloc(-2, 0);
			continue ;
		}
		cmdline = parser(arr);
		executor(cmdline, env);
		ft_malloc(-2, 0);
	}
}
