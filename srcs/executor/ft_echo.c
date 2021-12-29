/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:03:42 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/28 17:15:41 by tamighi          ###   ########.fr       */
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
	while (tmp)
	{
		if (ft_strcmp(tmp->content, "-n"))
			nb = 1;
		else
		{
			ft_putstr2(tmp->content);
			if (tmp->next && !ft_strcmp(tmp->next->content, "-n"))
				ft_putstr2(" ");
		}
		tmp = tmp->next;
	}
	if (!nb)
		ft_putstr2("\n");
	return (1);
}
