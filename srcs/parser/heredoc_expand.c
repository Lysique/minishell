/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:39:42 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/19 11:14:03 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_env_index(char **env, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		while (env[i][j] == var[j])
		{
			j++;
			if (env[i][j] == '=' && (var[j] == ' ' || var[j] == 34 || !var[j]
					|| var[j] == '$' || var[j] == 39 || var[j] == '*'
					|| var[j] == '\n'))
				return (i);
		}
		i++;
		j = 0;
	}
	return (i);
}

char	*heredoc_expand_to_env(char *var, char **env, int ix, int i)
{
	char	*new;
	int		j;
	int		k;

	new = malloc(ft_strlen(var) + ft_strlen(env[ix]) + 1);
	j = 0;
	k = 0;
	while (var[i] != '$' && var[i])
		new[k++] = var[i++];
	while (env[ix] && env[ix][j] != '=')
		j++;
	j++;
	while (env[ix] && env[ix][j])
		new[k++] = env[ix][j++];
	i++;
	while (var[i] && var[i] != ' ' && var[i] != 34
		&& var[i] != 39 && var[i] != '$' && var[i] != '*'
		&& var[i] != '\n')
		i++;
	while (var[i])
		new[k++] = var[i++];
	new[k] = '\0';
	free(var);
	return (new);
}

static char	*heredoc_special_expand(char *var, int exitstatus)
{
	int		i;
	int		j;
	int		x;
	char	*new;
	char	*nb;

	nb = ft_itoa(exitstatus);
	new = malloc(ft_strlen(var) + ft_strlen(nb) + 1);
	i = 0;
	j = 0;
	x = 0;
	while (var[x] != '$')
		new[i++] = var[x];
	x += 2;
	while (nb[j])
		new[i++] = nb[j++];
	while (var[x])
		new[i++] = var[x++];
	new[i] = '\0';
	free(nb);
	free(var);
	return (new);
}

char	*heredoc_expand(char *var, t_cmdline *cmdline)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		if (var[i] == '$' && var[i + 1])
		{
			if (var[i + 1] == '?')
				var = heredoc_special_expand(var, cmdline->exit);
			else
				var = heredoc_expand_to_env(var, cmdline->env,
						heredoc_env_index(cmdline->env, &var[i + 1]), 0);
			i = -1;
		}
	}
	return (var);
}
