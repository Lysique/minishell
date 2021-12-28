/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:00:28 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/28 09:42:17 by slathouw         ###   ########.fr       */
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

int	ft_exit(void *cmdline)
{
	int		num;
	t_cmds	cmd;

	cmd = *((t_cmdline *) cmdline)->cmds;
	if (cmd.args && is_number(cmd.args->content) && cmd.args->next)
	{
		printf("minishell: exit: too many arguments\n");
		return (0);
	}
	if (cmd.args && !is_number(cmd.args->content))
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n", 
				(char *) cmd.args->content);
		ft_malloc(-2, 0);
		exit(0);
	}
	printf("exit\n");
	if (cmd.args)
		num = ft_num_exit(cmd.args->content);
	else
		num = 0;
	ft_malloc(-2, 0);
	exit(num);
	return (1);
}
