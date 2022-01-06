/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:00:28 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/06 15:46:36 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_number(char *str)
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

int	ft_num_exit(char *str)
{
	long	num;
	long	sign;
	int		i;

	i = 0;
	num = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i])
	{
		num = num * 10;
		num += str[i] - '0';
		if (num > 2147483647 || num * sign < -2147483648)
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				str);
			ft_malloc(-2, 0);
			exit(0);
		}
		i++;
	}
	return (num);
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

int	ft_exit(t_cmdline *cmdline)
{
	int		num;
	t_cmds	cmd;

	cmd = *cmdline->cmds;
	if (cmd.args && is_number(cmd.args->content) && cmd.args->next)
	{
		ft_fdprintf(2, "minishell: exit: too many arguments\n");
		cmdline->exit = 1;
		return (1);
	}
	if (is_not_numeric(cmdline, cmd))
	{
		free_env(cmdline->env);
		free(cmdline->prompt);
		ft_malloc(-2, 0);
		exit(cmdline->exit);
	}
	if (cmd.args)
		num = ft_num_exit(cmd.args->content);
	else
		num = 0;
	if (cmdline->cmds->exitok == 0)
		exit(num);
	ft_putstr2("exit\n");
	ft_malloc(-2, 0);
	free_env(cmdline->env);
	free(cmdline->prompt);
	exit(num);
	return (num);
}
