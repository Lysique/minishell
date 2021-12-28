/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:03:42 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/28 13:41:35 by tamighi          ###   ########.fr       */
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

int	ft_strcmp2(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_cmdline *cmdline)
{
	t_args	*tmp;
	t_cmds	*cmds;
	int		nb;

	cmds = cmdline->cmds;
	tmp = cmds->args;
	nb = 0;
	if ((*(cmds + 1)).command != NULL && cmds->pipetype == 1)
		dup2(cmds->p[1], 1);
	while (tmp)
	{
		if (ft_strcmp2(tmp->content, "-n"))
			nb = 1;
		else
			ft_putstr2(tmp->content);
		tmp = tmp->next;
		if (tmp)
			ft_putstr2(" ");
	}
	if (!nb)
		ft_putstr2("\n");
	if (close(cmdline->cmds->p[0]) == -1)
		exit(EXIT_FAILURE);
	return (1);
}
