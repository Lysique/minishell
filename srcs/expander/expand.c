/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:13:51 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/08 11:28:59 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*split_cmd_to_args(char *cmd, t_args **args)
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

char	*split_content_to_args(char *content, t_args **argss)
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

char	*special_expand(char *var, int exitstatus)
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

char	*expand_return(char *var, t_args **args, int x)
{
	if (x)
		var = split_cmd_to_args(var, args);
	else
		var = split_content_to_args(var, args);
	printf("AFTER : %s\n", var);
	return (var);
}

char	*expand(char *var, t_cmdline *cmdline, int x)
{
	int	i;

	i = 0;
	printf("BEFORE : %s\n", var);
	if (var[i] == '*')
		var = expand_wildcard(var);
	while (var[i])
	{
		if (var[i] == 39)
		{
			i++;
			while (var[i] && var[i] != 39)
				i++;
		}
		if (var[i] == '$' && var[i + 1] == '?')
			var = special_expand(var, cmdline->exit);
		else if (var[i] == '$')
		{
			var = expand_to_env(var,
					cmdline->env, env_index(cmdline->env, &var[i + 1]), 0);
			i = 0;
		}
		else
			i++;
	}
	return (expand_return(var, &cmdline->cmds->args, x));
}
