/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:09:23 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/20 12:01:46 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmdline *cmdline)
{
	char	*line;
	int		pwd_index;

	line = getcwd(NULL, 0);
	if (!line)
	{
		pwd_index = env_find(cmdline, "PWD");
		line = ft_strtrim(cmdline->env[pwd_index], "PWD=");
	}
	printf("%s\n", line);
	if (line)
		free (line);
	return (EXIT_SUCCESS);
}
