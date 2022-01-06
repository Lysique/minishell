/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 06:57:35 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/06 05:26:39 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**get_dup_env(t_cmdline *cmdline)
{
	char	**dup;
	int		count;

	count = 0;
	while (cmdline->env[count])
		count++;
	dup = (char **) malloc(sizeof(char *) * (count + 1));
	dup[count] = NULL;
	count--;
	while (count > -1)
	{
		dup[count] = cmdline->env[count];
		count--;
	}
	return (dup);
}

static void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	print_export(char **env)
{
	int	i;
	int	j;
	int	flagequ;

	i = -1;
	while (env[++i])
	{
		flagequ = 1;
		j = -1;
		ft_putstr_fd("declare -x ", 1);
		while (env[i][++j])
		{
			ft_putchar_fd(env[i][j], 1);
			if (env[i][j] == '=' && flagequ && flagequ--)
				ft_putchar_fd('"', 1);
		}
		if (!flagequ)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
	}
}

static void	env_sort(t_cmdline *cmdline)
{
	char	**dup;
	int		i;
	int		j;

	dup = get_dup_env(cmdline);
	i = -1;
	while (dup[++i])
	{
		j = i;
		while (dup[++j])
		{
			if (ft_strcmp(dup[i], dup[j]) > 0)
				ft_swap(&dup[i], &dup[j]);
		}
	}
	print_export(dup);
	free(dup);
}

int	ft_export(t_cmdline *cmdline)
{
	t_args			*args;
	const t_cmds	cmd = *cmdline->cmds;
	int				fail;
	char			*argline;

	args = cmd.args;
	fail = 0;
	if (!args)
		env_sort(cmdline);
	while (args)
	{
		argline = (char *) args->content;
		if (!has_valid_identifier(argline))
		{
			ft_fdprintf(2, "minishell: export: '%s': not a valid identifier\n",
				argline);
			args = args->next;
			fail = 1;
			continue ;
		}
		env_add_var(cmdline, argline);
		args = args->next;
	}
	return (fail);
}
