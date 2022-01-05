/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:09:23 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/05 13:21:27 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmdline *cmdline)
{
	char	*line;

	line = ft_malloc(500, 0);
	line = getcwd(line, 500);
	printf("%s\n", line);
	if (close(cmdline->cmds->p[0]) == -1)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
