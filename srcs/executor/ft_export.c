/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 06:57:35 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/28 10:35:49 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(void *cmdline)
{
	t_args	*args;
	t_cmds	cmd;
	int		fail;
	char	*argline;

	cmd = *((t_cmdline *) cmdline)->cmds;
	args = cmd.args;
	fail = 0;
	if (!args)
		ft_env(((t_cmdline *) cmdline));
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
		env_add_var(((t_cmdline *) cmdline), argline);
//		ft_printf(BRED "%i set to %s\n" RESET,
//			env_find((t_cmdline *)cmdline,"SLATHOUW"), ((t_cmdline *)cmdline)->env[env_find((t_cmdline *)cmdline, "SLATHOUW")]);
		ft_env((t_cmdline *) cmdline);
		args = args->next;
	}
	ft_printf(BBLU "MY EXPORT\n" RESET);
	return (!fail);
}
