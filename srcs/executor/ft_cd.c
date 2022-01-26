/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:12:42 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/26 11:31:31 by tamighi          ###   ########.fr       */
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
	int			i;
	t_cmdline	*cl;

	cl = cl_ptr(NULL);
	i = env_find(cl, "HOME");
	if (i > -1)
		while (ft_srch(env[i++], "HOME=") == 0)
			;
	return (ms_strtrim(env[i], "HOME="));
}

int	cd_error(t_args *args)
{
	if (!args)
		ft_fdprintf(2, "minishell : You unsetted home :(\n");
	else
		ft_fdprintf(2, "minishell: cd: %s: No such directory\n",
			(char *) args->content);
	return (EXIT_FAILURE);
}

int	update_pwd(t_cmdline *cmdline, char *pwd, t_cmds cmd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = ft_strjoinfree(pwd, "/");
		cwd = ft_strjoinfree(cwd, cmd.args->content);
	}
	env_set(cmdline, "PWD", cwd);
	free (cwd);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_cmdline *cmdline)
{
	char	*pwd;
	char	*cwd;
	t_cmds	cmd;

	cmd = *cmdline->cmds;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = get_pwd(cmdline);
	if (!cmd.args)
	{
		free(pwd);
		pwd = cd_to_home(cmdline->env);
	}
	else if (chdir(cmd.args->content) != -1)
		return (update_pwd(cmdline, pwd, cmd));
	cwd = ft_pathjoin(pwd, cmd.args->content);
	free(pwd);
	if (!cwd || chdir(cwd) == -1)
		return (cd_error(cmd.args));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = cwd;
	env_set(cmdline, "PWD", pwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
