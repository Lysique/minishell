/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:58:53 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/04 13:54:52 by slathouw         ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}
