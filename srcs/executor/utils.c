/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:27:27 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/26 14:20:05 by slathouw         ###   ########.fr       */
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

char	*ms_strdup(char	*s)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = ft_malloc(sizeof(char) * (len + 1), 0);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}
