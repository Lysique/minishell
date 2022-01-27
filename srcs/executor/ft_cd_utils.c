/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:19:25 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/26 14:39:04 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd(t_cmdline *cmdline)
{
	char	*pwd;
	int		pwd_index;

	pwd_index = env_find(cmdline, "PWD");
	pwd = ft_strtrim(cmdline->env[pwd_index], "PWD=");
	return (pwd);
}

char	*get_cwd(char *pwd, t_cmds *cmd)
{
	char	*cwd;

	if (!cmd->args)
		cwd = ft_pathjoin(pwd, NULL);
	else
	{
		cwd = ft_pathjoin(pwd, cmd->args->content);
	}
	free(pwd);
	return (cwd);
}
