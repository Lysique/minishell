/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:27:27 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/26 12:51:33 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_srch(char *envp, char *var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (envp[i] != var[i])
			return (0);
		i++;
	}
	return (1);
}

void	restore_stds(int *fds)
{
	dup2(fds[4], 0);
	dup2(fds[5], 1);
}

void	close_fds(int *fds)
{
	int	i;

	i = -1;
	while (++i < 6)
		close(fds[i]);
}

char	*get_pwd(t_cmdline *cmdline)
{
	char	*pwd;
	int		pwd_index;

	pwd_index = env_find(cmdline, "PWD");
	pwd = ft_strtrim(cmdline->env[pwd_index], "PWD=");
	return (pwd);
}
