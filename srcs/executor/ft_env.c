/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:58:53 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/28 13:37:18 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(void *cmdline)
{
	char	**env;
	size_t	i;
	t_cmds	*cmds;

	env = ((t_cmdline *) cmdline)->env;
	i = -1;
	cmds = ((t_cmdline *) cmdline)->cmds;
	if ((*(cmds + 1)).command != NULL && cmds->pipetype == 1)
		dup2(cmds->p[1], 1);
	while (env[++i])
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], 1);
	ft_putendl_fd(BBLU "THIS IS MINE" RESET, 1);
	return (1);
}
