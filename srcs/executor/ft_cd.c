/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:12:42 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/26 14:44:17 by slathouw         ###   ########.fr       */
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
	if (!cd)
		return (ft_strdup(pwd));
	while (pwd[i])
		i++;
	while (cd[j])
		j++;
	new = malloc(i + j + 2);
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

static char	*cd_to_home(char **env)
{
	int			i;
	t_cmdline	*cl;

	cl = cl_ptr(NULL);
	i = env_find(cl, "HOME");
	if (i == -1)
		return (NULL);
	return (ft_strtrim(env[i], "HOME="));
}

static int	cd_error(t_args *args, char *cwd)
{
	ft_ptrdel(cwd);
	if (!args)
		ft_fdprintf(2, "minishell : You unsetted home :(\n");
	else
	{
		if (!access(args->content, F_OK))
			ft_fdprintf(2, "minishell: cd: %s: No such directory\n",
				(char *) args->content);
		else
			ft_fdprintf(2, "minishell: cd: %s: No such file or directory\n",
				(char *) args->content);
	}
	return (EXIT_FAILURE);
}

static int	update_pwd(t_cmdline *cmdline, char *pwd, t_cmds cmd)
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
	cwd = get_cwd(pwd, &cmd);
	if (!cwd || chdir(cwd) == -1)
		return (cd_error(cmd.args, cwd));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strjoinfree(pwd, cwd);
	env_set(cmdline, "PWD", pwd);
	free(cwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
