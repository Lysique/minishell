/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:00:28 by tamighi           #+#    #+#             */
/*   Updated: 2021/11/22 16:03:01 by tamighi          ###   ########.fr       */
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

int	ft_exit(t_cmds cmd)
{
	int	num;

	if (cmd.args && is_number(cmd.args->content) && cmd.args->next)
	{
		printf("minishell: exit: too many arguments\n");
		return (0);
	}
	if (cmd.args && !is_number(cmd.args->content))
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n", 
				cmd.args->content);
		ft_malloc(-2, 0);
		exit(0);
	}
	printf("exit\n");
	if (!cmd.args)
	{
		ft_malloc(-2, 0);
		exit(0);
	}
	num = ft_num_exit(cmd.args->content);
	ft_malloc(-2, 0);
	exit(num);
	return (1);
}
