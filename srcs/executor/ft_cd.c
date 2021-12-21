/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:12:42 by tamighi           #+#    #+#             */
/*   Updated: 2021/11/22 16:29:51 by tamighi          ###   ########.fr       */
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

int	ft_cd(t_cmds cmd)
{
	char	*pwd;

	if (!cmd.args)
		return (1);
	pwd = ft_malloc(500, 0);
	pwd = getcwd(pwd, 500);
	if (!pwd)
		return (-1);
	pwd = ft_pathjoin(pwd, cmd.args->content);
	if (chdir(pwd) == -1)
	{
		printf("minishell: cd: %s: No such directory\n", cmd.args->content);
		return (-1);
	}
	return (1);
}
