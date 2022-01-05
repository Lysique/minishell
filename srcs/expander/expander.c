/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:30:27 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/05 13:20:38 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fk_quotes(char *var)
{
	int		i;
	int		j;
	char	*new;
	char	quote;

	i = 0;
	j = 0;
	new = ft_malloc(ft_strlen(var) + 1, 0);
	while (var[i])
	{
		if (var[i] == 34 || var[i] == 39)
		{
			quote = var[i];
			while (var[++i] != quote && var[i])
				new[j++] = var[i];
			i++;
		}
		if (var[i])
			new[j++] = var[i++];
	}
	new[j] = 0;
	return (new);
}

char	*expand_to_env(char *var, char *env)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	new = ft_malloc(ft_strlen(var) + ft_strlen(env) + 1, 0);
	i = 0;
	j = 0;
	k = 0;
	while (var[i] != '$' && var[i])
		new[k++] = var[i++];
	while (env && env[j] != '=')
		j++;
	j++;
	while (env && env[j])
		new[k++] = env[j++];
	while (var[i] && var[i] != ' ' && var[i] != 34)
		i++;
	while (var[i])
		new[k++] = var[i++];
	new[k] = '\0';
	ft_malloc(-1, var);
	return (new);
}

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
			if (env[i][j] == '=' && (var[j] == ' ' || var[j] == 34 || !var[j]))
				return (i);
		}
		i++;
		j = 0;
	}
	return (i);
}

void	expander(t_cmdline *cmdline)
{
	t_args	*tmp;

	tmp = cmdline->cmds->args;
	cmdline->cmds->cmd = expand(cmdline->cmds->cmd, cmdline->env, tmp, 1);
	while (tmp)
	{
		tmp->content = expand(tmp->content, cmdline->env, tmp, 0);
		tmp = tmp->next;
	}
}
