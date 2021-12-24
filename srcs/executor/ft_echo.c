/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:03:42 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/24 08:10:00 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*TODO: echo should not use printf but instead ft_putstr_fd with fd = pipeout?*/
int	ft_echo(t_cmdline *cmdline)
{
	t_args	*tmp;
	t_cmds	cmd;

	cmd = *cmdline->cmds;
	tmp = cmd.args;
	while (tmp)
	{
		printf("%s", (char *) tmp->content);
		tmp = tmp->next;
		if (tmp)
			printf(" ");
	}
	printf("\n");
	return (1);
}
