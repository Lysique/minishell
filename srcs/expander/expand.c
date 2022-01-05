/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 13:48:15 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/05 12:30:30 by slathouw         ###   ########.fr       */
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

	arr = ms_split(cmd, ' ');
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

char	*split_content_to_lst(char *content, t_args **argss)
{
	char	**arr;
	int		i;
	t_args	*tmp;
	t_args	*args;

	arr = ms_split(content, ' ');
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
			if (env[i][j] == '=' && (var[j] == ' ' || !var[j]))
				return (i);
		}
		i++;
		j = 0;
	}
	return (-1);
}

char	*expand_to_env(char *var, char *env)
{
	char	*new;
	int		i;
	int		j;

	new = ft_malloc(ft_strlen(var) + ft_strlen(env) + 1, 0);
	i = 0;
	j = 0;
	while (var[i] != '$')
	{
		new[i] = var[i];
		i++;
	}
	while (env[j] != '=')
		j++;
	while (env[j++])
		new[i++] = env[j];
	ft_malloc(-1, var);
	return (new);
}

int	check_quotes(char **var)
{
	int		i;
	int		j;
	char	*new;
	char	quote;
	char	*tmp;

	i = 0;
	j = 0;
	quote = 0;
	tmp = *var;
	new = ft_malloc(ft_strlen(*var) + 1, 0);
	while (tmp[i])
	{
		if (tmp[i] == 39 || tmp[i] == 34)
		{
			quote = tmp[i++];
			while (tmp[i] != quote && tmp[i])
				new[j++] = tmp[i++];
		}
		else
			new[j++] = tmp[i];
		if (tmp[i])
			i++;
	}
	new[j] = 0;
	*var = new;
	return (quote);
}

char	*expand(char *var, char **env, t_args **args, int x)
{
	int	i;
	int	quote;

	i = 0;
	if (x && var[i] == '*')
		return (split_cmd_to_args(expand_wildcard(var), args));
	else if (!x && var[i] == '*')
		return (split_content_to_lst(expand_wildcard(var), args));
	quote = check_quotes(&var);
	while (var[i])
	{
		if (var[i] == '$' && env_index(env, &var[i + 1]) != -1)
		{
			if (quote != 39)
			{
				var = expand_to_env(var, env[env_index(env, &var[i + 1])]);
				i = -1;
			}
		}
		i++;
	}
	if (x && !quote)
		return (split_cmd_to_args(var, args));
	else if (!x && !quote)
		return (split_content_to_lst(var, args));
	return (var);
}
