/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:03:42 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/22 14:32:33 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_cmdline *cmdline)
{
	t_args	*tmp;
	t_cmds	cmd;

	cmd = *cmdline->cmds;
	tmp = cmd.args;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
		if (tmp)
			printf(" ");
	}
	printf("\n");
	return (1);
}
