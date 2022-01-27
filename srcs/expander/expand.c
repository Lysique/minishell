/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:39:25 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/27 18:17:50 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_index(char **env, char *var)
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
					|| var[j] == '$' || var[j] == 39 || var[j] == '*'))
				return (i);
		}
		i++;
		j = 0;
	}
	return (i);
}

char	*special_expand(char *var, int exitstatus, int index)
{
	int		i;
	int		j;
	int		k;
	char	*new;
	char	*nb;

	nb = ft_itoa(exitstatus);
	new = ft_malloc(ft_strlen(var) + ft_strlen(nb) + 1, 0);
	i = 0;
	j = 0;
	k = 0;
	while (k < index)
		new[i++] = var[k++];
	k += 2;
	while (nb[j])
		new[i++] = nb[j++];
	while (var[k])
		new[i++] = var[k++];
	new[i] = '\0';
	free(nb);
	ft_malloc(-1, var);
	return (new);
}

char	*nb_expand(char *var, int index)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_malloc(ft_strlen(var) - 1, 0);
	while (i < index)
	{
		new[i] = var[i];
		i++;
	}
	while (var[i + 2])
	{
		new[i] = var[i + 2];
		i++;
	}
	ft_malloc(-1, var);
	return (new);
}

char	*envir_expand(char *var, char **env, int index, int i)
{
	char	*new;
	int		j;
	int		k;
	int		i_env;

	i_env = env_index(env, &var[index + 1]);
	new = ft_malloc(ft_strlen(var) + ft_strlen(env[i_env]) + 1, 0);
	j = 0;
	k = 0;
	while (i < index)
		new[k++] = var[i++];
	i += 1;
	while (env[i_env] && env[i_env][j - 1] != '=')
		j++;
	while (env[i_env] && env[i_env][j])
		new[k++] = env[i_env][j++];
	while (var[i] && var[i] != ' ' && var[i] != 34
		&& var[i] != 39 && var[i] != '$' && var[i] != '*')
		i++;
	while (var[i])
		new[k++] = var[i++];
	new[k] = '\0';
	ft_malloc(-1, var);
	return (new);
}

char	*expand_dollar(char *var, t_cmdline *cmdline, int index)
{
	if (var[index + 1] == '?')
		return (special_expand(var, cmdline->exit, index));
	else if (var[index + 1] >= 0 && var[index + 1] <= 9)
		return (nb_expand(var, index));
	else
		return (envir_expand(var, cmdline->env, index, 0));
}
