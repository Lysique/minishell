/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:03:16 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/28 10:43:57 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>       
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include "../libs/libftprintf/includes/ft_printf_bonus.h"
# include "../libs/libftprintf/includes/ft_array.h"
# include "print_colors.h"

/*STRUCTS*/

typedef t_list	t_args;

typedef struct s_lstfiles
{
	int					fd;
	struct s_lstfiles	*next;
}				t_lstfiles;

typedef struct s_cmds
{
	char		*command;
	char		*cmd;
	t_args		*args;
	t_lstfiles	*outfiles;
	t_lstfiles	*infiles;
	int			parentheses;
	int			exitstatus;
	int			pipetype;
	int			fd_out;
	int			fd_in;
	int			p[2];
}				t_cmds;

typedef struct s_builtins
{
	char	*builtin;
	int		(*fct)(void *cmdline);
}				t_builtins;

typedef struct s_cmdline
{
	char				**env;
	t_builtins			builtins[8];
	t_cmds				*cmds;
	t_array				env_arr;
}			t_cmdline;

/*FUNCTIONS*/

void		execute_minishell(char **env);
void		signal_management(void);
void		*ft_malloc(int size, void *p);
char		*check_cmdline(char **arr);

	/*LEXER*/

char		**lexer(char *line);
int			nb_tokens(char *line);
char		**tokens_in_arr(char *line, char **arr);

	/*PARSER*/

t_cmdline	*parser(char **arr);
t_cmdline	*create_cmdline(char **arr, t_cmdline *cmdline);
t_cmds		cmds_add_lstfile(char **arr, t_cmds cmds);
void		create_command(t_cmdline *cmdline, int nb_cmds);
int			nb_cmds(char **arr);

	/*EXPANDER*/

	/*EXECUTOR*/

void		executor(t_cmdline *cmdline);
void		check_exit_status(t_cmds **cmds);

int			ft_exit(void *cmdline);
int			ft_echo(void *cmdline);
int			ft_pwd(void *cmdline);
int			ft_cd(void *cmdline);
int			ft_env(void *cmdline);
int			ft_export(void *cmdline);

/*ENV FUNCTIONS*/
void		env_init(char **envp, t_cmdline *cmdline);
int			has_valid_identifier(char *line);
int			is_nameequword_format(char *name);
int			env_add_var(t_cmdline *cmdline, char *line);
int			env_set_var(t_cmdline *cmdline, char *linedup, int env_index);
int			env_find(t_cmdline *cmdline, char *name);

void		pipex(t_cmdline *cmdline);
void		redir_exec(t_cmdline *cmdline);
int			check_if_builtin(t_cmdline *cmdline, t_builtins *builtins);
int			is_cd_or_exit(t_cmdline *cmdline);
char		**ft_split(char const *s, char c);
char		*find_path(char *cmd, char **envp);

int			ft_srch(char *envp);
int			ft_check(char s1, char *set);
#endif
