/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 08:36:08 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/24 08:23:44 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*split_cmd_to_args(char *cmd, t_args **args)
{
	char	**arr;
	int		i;
	t_args	*tmp;
	t_args	*tmp2;
	t_args	*tmp3;

	arr = expander_split(cmd);
	i = 1;
	while (arr[i])
	{
		tmp = ft_malloc(sizeof(t_args), 0);
		tmp->next = *args;
		tmp->content = arr[i];
		if (i++ == 1)
			tmp3 = tmp;
		else
			tmp2->next = tmp;
		tmp2 = tmp;
	}
	if (i != 1)
		*args = tmp3;
	return (arr[0]);
}

static char	*split_content_to_args(char *content, t_args **argss)
{
	char	**arr;
	int		i;
	t_args	*tmp;
	t_args	*args;

	arr = expander_split(content);
	args = *argss;
	i = 1;
	while (arr[i])
	{
		tmp = ft_malloc(sizeof(t_args), 0);
		tmp->next = args->next;
		args->next = tmp;
		args = args->next;
		tmp->content = arr[i];
		tmp = tmp->next;
		i++;
	}
	return (arr[0]);
}

static char	*special_expand(char *var, int exitstatus)
{
	int		i;
	int		j;
	char	*new;
	char	*nb;

	nb = ft_itoa(exitstatus);
	new = ft_malloc(ft_strlen(var) + ft_strlen(nb) + 1, 0);
	i = 0;
	j = 0;
	while (*var != '$')
	{
		new[i++] = *var;
		var++;
	}
	var += 2;
	while (nb[j])
		new[i++] = nb[j++];
	while (*var)
	{
		new[i++] = *var;
		var++;
	}
	new[i] = '\0';
	free(nb);
	return (new);
}

static char	*expand_return(char *var, t_args **args, int x)
{
	var = expand_wildcard(var);
	if (x)
		var = split_cmd_to_args(var, args);
	else
		var = split_content_to_args(var, args);
	return (var);
}

char	*expand(char *var, t_cmdline *cmdline, int x)
{
	int	i;
	int	double_quote;

	i = -1;
	double_quote = -1;
	while (var[++i])
	{
		if (var[i] == 39 && double_quote == -1 && ++i)
		{
			while (var[i] && var[i] != 39)
				i++;
		}
		if (var[i] == 34)
			double_quote = double_quote * -1;
		else if (var[i] == '$' && var[i + 1])
		{
			if (var[i + 1] == '?')
				var = special_expand(var, cmdline->exit);
			else
				var = expand_to_env(var, cmdline->env,
						env_index(cmdline->env, &var[i + 1]), 0);
			i = -1;
		}
	}
	return (expand_return(var, &cmdline->cmds->args, x));
}
