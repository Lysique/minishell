/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 10:56:36 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/24 09:14:51 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_init(char **envp, t_cmdline *cmdline)
{
	char	*line;
	
	ft_array_init(&cmdline->env_arr, sizeof(char *));
	while (*envp)
	{
		line = ft_strdup(*envp);
		ft_array_add(&cmdline->env_arr, &line);
		envp++;
	}
	ft_array_add(&cmdline->env_arr, 0);
	cmdline->env = cmdline->env_arr.data;
}

/* 	char	**new_env;
	char	**temp;
	size_t	var_count;
	size_t	i;

	var_count = 0;
	temp = envp;
	while (*temp++)
		var_count++;
	new_env = ft_calloc(var_count + 1, sizeof(char *));
	i = -1;
	while (++i < var_count)
		new_env[i] = ft_strdup(envp[i]);
	return (new_env); */