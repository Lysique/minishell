/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 06:57:35 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/04 14:58:58 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_cmdline *cmdline)
{
	t_args			*args;
	const t_cmds	cmd = *cmdline->cmds;
	int				fail;
	char			*argline;

	args = cmd.args;
	fail = 0;
	if (!args)
		ft_env(cmdline);
	while (args)
	{
		argline = (char *) args->content;
		ft_printf("ARG = |%s|\n", argline);
		if (!has_valid_identifier(argline))
		{
			ft_fdprintf(2, "minishell: export: '%s': not a valid identifier\n",
				argline);
			args = args->next;
			fail = 1;
			continue ;
		}
		env_add_var(cmdline, argline);
		args = args->next;
	}
	return (fail);
}
