/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 08:30:13 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/28 12:25:04 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_minishell(char **env)
{
	char		**arr;
	char		*line;
	t_cmdline	cmdline;

	signal_management();
	while (1)
	{
		line = readline(BMAG "🤪 minishell 👉 " RESET);
		if (!line)
			exit(0);
		if (!*line)
			continue ;
		add_history(line);
		arr = lexer(line);
		if (check_cmdline(arr))
		{
			printf("minishell : syntax error near token '%s'\n", check_cmdline(arr));
			ft_malloc(-2, 0);
			continue ;
		}
		parser(arr, &cmdline);
		env_init(env, &cmdline);
		executor(&cmdline);
		ft_malloc(-2, 0);
	}
}
