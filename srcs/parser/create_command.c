/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:33:01 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/13 16:47:40 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_argjoin(char *command, char *arg)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (command && command[i])
		i++;
	while (arg && arg[j])
		j++;
	new = ft_malloc(i + j + 2, 0);
	i = 0;
	j = 0;
	while (command && command[i])
		new[j++] = command[i++];
	new[j++] = ' ';
	i = 0;
	while (arg && arg[i])
		new[j++] = arg[i++];
	new[j] = 0;
	return (new);
}

char	*join_cmds_arg(t_cmds cmd)
{
	t_list	*args;
	char	*command;
	char	*tmp;

	if (!cmd.args)
		return (ft_argjoin(cmd.cmd, 0));
	args = cmd.args;
	command = ft_argjoin(cmd.cmd, args->content);
	args = args->next;
	while (args)
	{
		tmp = command;
		command = ft_argjoin(command, args->content);
		ft_malloc(-1, tmp);
		args = args->next;
	}
	return (command);
}

void	create_command(t_cmdline *cmdline, int nb_cmds)
{
	int	i;

	i = 0;
	while (i < nb_cmds)
	{
		cmdline->cmds[i].command = join_cmds_arg(cmdline->cmds[i]);
		i++;
	}
}
