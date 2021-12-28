/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:12:42 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/28 13:40:19 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_pathjoin(char *pwd, char *cd)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (pwd[i])
		i++;
	while (cd[j])
		j++;
	new = ft_malloc(i + j + 2, 0);
	i = 0;
	j = 0;
	while (pwd[i])
	{
		new[i] = pwd[i];
		i++;
	}
	new[i++] = '/';
	while (cd[j])
		new[i++] = cd[j++];
	new[i] = '\0';
	return (new);
}

char	*cd_to_home(char **env)
{
	int	i;

	i = 0;
	while (ft_srch(env[i], "HOME=") == 0)
		i++;
	return (ft_strtrim(env[i], "HOME="));
}

int	ft_cd(t_cmdline *cmdline)
{
	char	*pwd;
	t_cmds	cmd;

	cmd = *cmdline->cmds;
	pwd = ft_malloc(500, 0);
	pwd = getcwd(pwd, 500);
	if (!pwd)
		return (-1);
	if (!cmd.args)
		pwd = cd_to_home(cmdline->env);
	else
		pwd = ft_pathjoin(pwd, cmd.args->content);
	if (chdir(pwd) == -1)
	{
		printf("minishell: cd: %s: No such directory\n", (char *) cmd.args->content);
		return (-1);
	}
	return (1);
}
