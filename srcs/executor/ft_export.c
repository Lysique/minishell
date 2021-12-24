/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 06:57:35 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/24 08:14:52 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_cmdline *cmdline)
{
	t_args	*args;
	t_cmds	cmd;

	cmd = *cmdline->cmds;
	args = cmd.args;
	if (!args)
		ft_env(cmdline);
	ft_printf(BBLU "MY EXPORT\n" RESET);
	return (1);
}
