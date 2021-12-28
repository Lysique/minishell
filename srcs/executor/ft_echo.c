/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:03:42 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/28 09:43:42 by slathouw         ###   ########.fr       */
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

int	ft_echo(void *cmdline)
{
	t_args	*tmp;
	t_cmds	*cmds;

	cmds = ((t_cmdline *) cmdline)->cmds;
	tmp = cmds->args;
	if ((*(cmds + 1)).command != NULL && cmds->pipetype == 1)
		dup2(cmds->p[1], 1);
	while (tmp)
	{
		ft_putstr2(tmp->content);
		tmp = tmp->next;
		if (tmp)
			ft_putstr2(" ");
	}
	ft_putstr2("\n");
	if (close(((t_cmdline *) cmdline)->cmds->p[0]) == -1)
		exit(EXIT_FAILURE);
	return (1);
}
