/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 10:56:36 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/23 10:59:45 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_init(char **envp)
{
	char	**new_env;
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
	return (new_env);
}
