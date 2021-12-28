/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:06:38 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/28 15:43:03 by slathouw         ###   ########.fr       */
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
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd("': not enough arguments\n", 2);
		fail = 1;
		return (!fail);
	}
	while (args)
	{
		argline = (char *) args->content;
		if (is_nameequword_format(argline) != 2)
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(argline, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			fail = 1;
			continue ;
		}
		env_unset(cmdline, argline);
		args = args->next;
	}
	return (!fail);
}
