/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:47:11 by tamighi           #+#    #+#             */
/*   Updated: 2021/11/21 14:25:07 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n#minishell: ");
	}
}

void	signal_management(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sig_handler;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &sa, 0);
}
