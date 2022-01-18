/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:10:46 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/18 09:11:22 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_add_var(t_cmdline *cmdline, char *line)
{
	char	*equptr;
	char	*name;
	int		env_index;
	char	*env_line;

	if (is_nameequword_format(line) != 1)
		return (0);
	equptr = ft_strchr(line, '=');
	name = ft_substr(line, 0, equptr - line);
	env_index = env_find(cmdline, name);
	free(name);
	env_line = ft_strdup(line);
	if (env_index != -1)
		env_set_line_at_index(cmdline, env_line, env_index);
	else
		ft_array_add(&cmdline->env_arr, &env_line);
	cmdline->env = (char **)cmdline->env_arr.data;
	return (1);
}

int	env_set_line_at_index(t_cmdline *cmdline, char *linedup, int env_index)
{
	char	**env;

	env = cmdline->env;
	if (env[env_index])
		free(env[env_index]);
	env[env_index] = linedup;
	return (1);
}

int	env_unset(t_cmdline *cmdline, char *var_name)
{
	int		env_index;
	char	**env;

	env = cmdline->env;
	env_index = env_find(cmdline, var_name);
	if (env_index < 0)
		return (0);
	env[env_index] = NULL;
	while ((size_t)++env_index < cmdline->env_arr.count && env[env_index])
	{
		env[env_index - 1] = env[env_index];
		env[env_index] = NULL;
	}
	cmdline->env_arr.count--;
	return (1);
}

int	env_set(t_cmdline *cmdline, char *name, char *value)
{
	char	*tmp;
	char	*envline;
	int		env_index;

	tmp = ms_strjoin(name, "=");
	envline = ft_strjoin(tmp, value);
	ft_malloc (-1, tmp);
	env_index = env_find(cmdline, name);
	if (env_index != -1)
		env_set_line_at_index(cmdline, envline, env_index);
	else
		ft_array_add(&cmdline->env_arr, &envline);
	cmdline->env = (char **)cmdline->env_arr.data;
	return (1);
}
