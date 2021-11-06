/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 09:59:19 by slathouw          #+#    #+#             */
/*   Updated: 2021/11/06 10:34:29 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	int	fd = open("Makefile", O_RDONLY);
	char *line = get_next_line(fd);
	while (line)
	{
		ft_printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	ft_printf("%s\n", line);
	close(fd);
	return (0);
}
