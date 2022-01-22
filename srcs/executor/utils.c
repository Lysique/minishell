/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:27:27 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/22 15:01:56 by slathouw         ###   ########.fr       */
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

void	free_all_and_exit(t_cmdline *cmdline, int num)
{
	close_fds(cmdline->fds);
	free_env(cmdline->env);
	free(cmdline->prompt);
	ft_malloc(-2, 0);
	if (num == -1)
		exit(cmdline->exit);
	exit(num);
}
