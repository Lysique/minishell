/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 10:56:36 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/28 15:34:40 by slathouw         ###   ########.fr       */
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
	cmdline->env = cmdline->env_arr.data;
	ft_printf(BYEL "env set\n" RESET);
}

int	has_valid_identifier(char *line)
{
	int	i;
	int	has_alpha;

	i = -1;
	has_alpha = 0;
	if (!line || !*line || *line == '=')
		return (0);
	while (line[++i] && line[i] != '=')
	{
		if (ft_isalpha(line[i]))
			has_alpha = 1;
		else
		{
			if (ft_isdigit(line[i]) && !has_alpha)
				return (0);
			else if (!ft_isdigit(line[i]) && line[i] != '_')
				return (0);
		}
	}
	return (1);
}
/*Checks env_var format
	RETURNS: 	
	- 1 if name=word format
	- 2 if name format
	- 0 if invalid identifier
*/
int	is_nameequword_format(char *name)
{
	char	*equptr;

	equptr = ft_strchr(name, '=');
	if (!has_valid_identifier(name))
		return (0);
	if (!equptr)
		return (2);
	return (1);
}

int	env_find(t_cmdline *cmdline, char *name)
{
	const char	**env = (const char **) cmdline->env;
	int			i;
	int			j;

	i = -1;
	if (!env)
		return (-1);
	while (env[++i])
	{
		j = 0;
		while (env[i][j] == name[j])
			j++;
		if (env[i][j] == '=' && !name[j])
			return (i);
	}
	return (-1);
}

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
	ft_printf(BRED "%i set to %s\n" RESET, env_index, env[env_index]);
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
	while (++env_index < (int) cmdline->env_arr.count && env[env_index])
	{
		env[env_index - 1] = env[env_index];
		env[env_index] = NULL;
	}
	cmdline->env_arr.count--;
	return (1);
}

int env_set(t_cmdline *cmdline, char *name, char *value)
{
	char	*tmp;
	char	*envline;
	int		env_index;

	tmp = ft_strjoin(name, "=");
	envline = ft_strjoin(tmp, value);
	free (tmp);
	env_index = env_find(cmdline, name);
	if (env_index != -1)
		env_set_line_at_index(cmdline, envline, env_index);
	else
		ft_array_add(&cmdline->env_arr, &envline);
	cmdline->env = (char **)cmdline->env_arr.data;
	return (1);
}
