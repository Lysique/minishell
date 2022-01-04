/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:06:38 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/04 14:42:37 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_cmdline *cmdline)
{
	t_args	*args;
	t_cmds	cmd;
	int		fail;
	char	*argline;

	cmd = *cmdline->cmds;
	args = cmd.args;
	fail = 0;
	if (!args)
		return (EXIT_SUCCESS);
	while (args)
	{
		argline = (char *) args->content;
		if (is_nameequword_format(argline) != 2)
		{
			ft_fdprintf(2, "minishell: export: '%s': not a valid identifier\n",
				argline);
			fail = 1;
			continue ;
		}
		env_unset(cmdline, argline);
		args = args->next;
	}
	return (fail);
}
