/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:00:28 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/31 13:04:50 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_num_exit(t_cmdline *cl, char *str)
{
	int			overflow_flag;
	long long	num;

	num = ft_atoll_overflow(str, 0, &overflow_flag);
	if (overflow_flag == 1)
	{
		ft_fdprintf(2, "exit\nminishell: exit: %s: numeric argument required\n",
			(char *) cl->cmds->args->content);
		cl->exit = 255;
		free_all_and_exit(cl, -1);
	}
	return (num % 256);
}

static int	is_not_numeric(t_cmdline *cmdline, t_cmds cmd)
{
	if (cmd.args && !is_number(cmd.args->content))
	{
		ft_fdprintf(2, "exit\nminishell: exit: %s: numeric argument required\n",
			(char *) cmd.args->content);
		ft_malloc(-2, 0);
		cmdline->exit = 255;
		return (1);
	}
	return (0);
}

static int	exit_error(t_cmdline *cmdline)
{
	ft_fdprintf(2, "minishell: exit: too many arguments\n");
	cmdline->exit = 1;
	return (1);
}

int	ft_exit(t_cmdline *cmdline)
{
	int		num;
	t_cmds	cmd;

	cmd = *cmdline->cmds;
	if (cmd.args && is_number(cmd.args->content) && cmd.args->next)
		return (exit_error(cmdline));
	if (is_not_numeric(cmdline, cmd))
		free_all_and_exit(cmdline, -1);
	if (cmd.args)
		num = ft_num_exit(cmdline, cmd.args->content);
	else
		num = cmdline->exit;
	if (cmdline->cmds->exitok == 0)
		free_all_and_exit(cmdline, num);
	ft_fdprintf(2, "exit\n", num);
	free_all_and_exit(cmdline, num);
	return (num);
}
