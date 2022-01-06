/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:03:42 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/06 04:39:19 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_n_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_putstr2(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
}

int	ft_echo(t_cmdline *cmdline)
{
	t_args	*tmp;
	int		nb;

	tmp = cmdline->cmds->args;
	nb = 0;
	if (tmp && check_n_arg(tmp->content))
	{
		tmp = tmp->next;
		nb = 1;
	}
	while (tmp && tmp->content)
	{
		ft_putstr2(tmp->content);
		if (tmp->next)
			ft_putstr2(" ");
		tmp = tmp->next;
	}
	if (!nb)
		ft_putstr2("\n");
	return (EXIT_SUCCESS);
}
