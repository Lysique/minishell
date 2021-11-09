/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:03:16 by slathouw          #+#    #+#             */
/*   Updated: 2021/11/09 15:28:19 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include "../libs/libftprintf/includes/ft_printf_bonus.h"

/*STRUCTS*/

typedef	t_list t_args;

typedef struct s_cmds
{
	char	*cmd;
	t_args	*args;
	int		pipein;
	int		pipeout;
} 				t_cmds;

typedef struct s_cmdline
{
	t_cmds *cmds;
	int	outfile;          
	int infile;
	int errfile;
}			t_cmdline;

/*FUNCTIONS*/
	/*LEXER*/

	/*PARSER*/

	/*EXPANDER*/

	/*EXECUTOR*/

#endif