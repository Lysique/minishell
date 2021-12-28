/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 06:57:35 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/28 15:38:27 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_cmdline *cmdline)
{
	t_args	*args;
	t_cmds	cmd;
	int		fail;
	char	*argline;

	cmd = *cmdline->cmds;
	args = cmd.args;
	fail = 0;
	if (!args)
		ft_env(cmdline);
	while (args)
	{
		argline = (char *) args->content;
		if (!has_valid_identifier(argline))
		{
			//TODO: refactor to correct error handler
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(argline, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			fail = 1;
			continue ;
		}
		env_add_var(cmdline, argline);
		args = args->next;
	}
	return (!fail);
}
