/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:13:51 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/05 13:21:26 by tamighi          ###   ########.fr       */
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

	arr = ft_split(cmd, ' ');
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

	arr = ft_split(content, ' ');
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

char	*expand(char *var, char **env, t_args *args, int x)
{
	int	i;

	i = 0;
	if (var[i] == '*')
		var = expand_wildcard(var);
	while (var[i])
	{
		if (var[i] == '$')
		{
			var = expand_to_env(var, env[env_index(env, &var[i + 1])]);
			i = 0;
		}
		i++;
	}
	var = fk_quotes(var);
	if (x)
		var = split_cmd_to_args(var, &args);
	else
		var = split_content_to_args(var, &args);
	return (var);
}
