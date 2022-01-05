/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:03:42 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/05 16:48:13 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (tmp && ft_strequ(tmp->content, "-n"))
	{
		tmp = tmp->next;
		nb = 1;
	}
	while (tmp)
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
