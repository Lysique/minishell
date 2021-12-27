/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:58:53 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/24 05:59:32 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_cmdline *cmdline)
{
	char	**env;
	size_t	i;

	env = cmdline->env;
	i = -1;
	while (env[++i])
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], 1);
	ft_putendl_fd(BBLU "THIS IS MINE" RESET, 1);
	return (1);
}
