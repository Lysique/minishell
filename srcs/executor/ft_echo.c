/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:03:42 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/22 13:12:04 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_cmds cmd)
{
	t_args	*tmp;

	tmp = cmd.args;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
		if (tmp)
			printf(" ");
	}
	printf("\n");
	return (1);
}
