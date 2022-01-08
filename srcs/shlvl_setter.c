/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_setter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:46:57 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/08 13:07:14 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	shlvl_atoi(t_cmdline *cmdline, int index)
{
	int		i;
	char	*c;
	int		nb;

	c = cmdline->env[index];
	i = 0;
	while (c[i] != '=')
		i++;
	i++;
	nb = 0;
	if (c[i] == '-')
		return (-1);
	if (c[i] == '+')
		i++;
	while (c[i])
	{
		if (c[i] < '0' || c[i] > '9')
			return (0);
		nb *= 10;
		nb += (c[i++] - '0');
	}
	return (nb);
}

void	shlvl_setter(t_cmdline *cmdline)
{
	int		nb;
	int		i;
	char	*c;

	i = env_find(cmdline, "SHLVL");
	if (i == -1)
	{
		env_set(cmdline, "SHLVL", "0");
		return ;
	}
	nb = shlvl_atoi(cmdline, i);
	c = ft_itoa(nb + 1);
	env_set(cmdline, "SHLVL", c);
	free(c);
}
