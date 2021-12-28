/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:09:23 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/28 13:43:41 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmdline *cmdline)
{
	char	*line;
	t_cmds	*cmds;

	cmds = cmdline->cmds;
	if ((*(cmds + 1)).command != NULL && cmds->pipetype == 1)
		dup2(cmds->p[1], 1);
	line = ft_malloc(500, 0);
	line = getcwd(line, 500);
	printf("%s\n", line);
	if (close(cmdline->cmds->p[0]) == -1)
		exit(EXIT_FAILURE);
	return (1);
}
