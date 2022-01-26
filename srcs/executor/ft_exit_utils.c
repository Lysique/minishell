/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:39:04 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/26 12:51:44 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long long	ft_atoll_overflow(const char *str, int i, int *flag)
{
	int			j;
	long		neg;
	long long	sum;

	neg = 1;
	sum = 0;
	j = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] && (ft_isspace(str[i]) || str[i] == '0'))
		i++;
	while (str[i] >= '0' && str[i] <= '9' && ++j)
	{
		sum = (sum * 10) + (str[i] - 48);
		if (((i == 18 && neg == 1) && (str[i] > '7' && str[i] <= '9'))
			|| ((i == 19 && neg == -1) && (str[i] == '9')))
			*flag = 1;
		i++;
	}
	while (str[i++])
		j++;
	if ((j > 19 && neg == 1) || (j > 20 && neg == -1))
		*flag = 1;
	return (sum * neg);
}

void	free_all_and_exit(t_cmdline *cmdline, int num)
{
	close_fds(cmdline->fds);
	free_env(cmdline->env);
	free(cmdline->prompt);
	ft_malloc(-2, 0);
	if (num == -1)
		exit(cmdline->exit);
	exit(num);
}
