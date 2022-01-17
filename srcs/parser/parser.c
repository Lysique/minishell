/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:18:31 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/17 07:47:41 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	nb_cmds(char **arr)
{
	int	i;

	i = 1;
	while (*arr)
	{
		if (**arr == '|' || **arr == '&')
			i++;
		arr++;
	}
	return (i);
}

void	cmdline_init(char **arr, t_cmdline *cmdline)
{
	int			i;

	i = nb_cmds(arr);
	cmdline->cmds = ft_malloc(sizeof(t_cmds) * (nb_cmds(arr) + 1), 0);
	cmdline->cmds[i].command = 0;
	while (i != -1)
	{
		cmdline->cmds[i].outfiles = 0;
		cmdline->cmds[i].infiles = 0;
		cmdline->cmds[i].parentheses = 0;
		cmdline->cmds[i].cmd = 0;
		cmdline->cmds[i].args = 0;
		cmdline->cmds[i].pipetype = 0;
		cmdline->cmds[i].exitstatus = 0;
		cmdline->cmds[i].exitok = 0;
		cmdline->cmds[i].fd_in = 0;
		cmdline->cmds[i].fd_out = 1;
		cmdline->cmds[i].p[0] = 0;
		cmdline->cmds[i].p[1] = 0;
		i--;
	}
}

void	parser(char **arr, t_cmdline *cmdline)
{
	cmdline_init(arr, cmdline);
	create_cmdline(arr, cmdline);
	create_command(cmdline, nb_cmds(arr));
}
