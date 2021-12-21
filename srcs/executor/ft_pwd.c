/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:09:23 by tamighi           #+#    #+#             */
/*   Updated: 2021/11/22 15:15:29 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmds cmd)
{
	char	*line;

	(void)cmd;
	line = ft_malloc(500, 0);
	line = getcwd(line, 500);
	printf("%s\n", line);
	return (1);
}
