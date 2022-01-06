/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:18:31 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/06 13:10:08 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_cmdline(t_cmdline *cmdline, int nb)
{
	int	i;
	
	i = 0;
	while (nb--)
	{
		printf("Command %d :\n", i + 1);
		printf("parentheses = %d\n", cmdline->cmds[i].parentheses);
		printf("command = %s, args = ", cmdline->cmds[i].cmd);
		while (cmdline->cmds[i].args)
		{
			printf("%s || ", (char *) cmdline->cmds[i].args->content);
			cmdline->cmds[i].args = cmdline->cmds[i].args->next;
		}
		printf("\n");
		printf("outfiles = ");
		while (cmdline->cmds[i].outfiles)
		{
			printf("fd : %d, ", cmdline->cmds[i].outfiles->fd);
			cmdline->cmds[i].outfiles = cmdline->cmds[i].outfiles->next;
		}
		printf("\ninfiles = ");	
		while (cmdline->cmds[i].infiles)
		{
			printf("fd : %d, ", cmdline->cmds[i].infiles->fd);
			cmdline->cmds[i].infiles = cmdline->cmds[i].infiles->next;
		}
		printf("\n");
		printf("pipetype : %d\n", cmdline->cmds[i].pipetype);
		printf("\n");
		i++;
	}
}

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
	while (i)
	{
		cmdline->cmds[i].outfiles = 0;
		cmdline->cmds[i].infiles = 0;
		cmdline->cmds[i].parentheses = 0;
		cmdline->cmds[i].cmd = 0;
		cmdline->cmds[i].args = 0;
		cmdline->cmds[i].pipetype = 0;
		i--;
	}
}

void	parser(char **arr, t_cmdline *cmdline)
{
	cmdline_init(arr, cmdline);
	create_cmdline(arr, cmdline);
	create_command(cmdline, nb_cmds(arr));
//	print_cmdline(cmdline, nb_cmds(arr));
}
