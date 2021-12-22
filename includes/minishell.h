/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:03:16 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/22 14:12:42 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>       
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include "../libs/libftprintf/includes/ft_printf_bonus.h"

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
	int			pipein;
	int			pipeout;
}				t_cmds;

typedef struct s_cmdline
{
	char				**env;
	struct s_builtins	*builtins;
	t_cmds				*cmds;
}			t_cmdline;

typedef struct s_builtins
{
	char	*builtin;
	int		(*fct)(t_cmdline *cmdline);
}				t_builtins;

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

void		executor(t_cmdline *cmdline, char **env);

int			ft_exit(t_cmdline *cmdline);
int			ft_echo(t_cmdline *cmdline);
int			ft_pwd(t_cmdline *cmdline);
int			ft_cd(t_cmdline *cmdline);

int			ft_srch(char *envp);
int			ft_check(char s1, char *set);

void		pipex(t_cmdline *cmdline);
void		loop_pipe(t_cmdline *cmdline, int fd_in);
void		redir_exec(int fd_in, t_cmds *cmds, int *p, t_cmdline *cmdline);
int			check_if_builtin(t_cmdline *cmdline, t_builtins *builtins);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
char		*ft_splitfct(char const *s, char c);
char		*ft_word(char const *s, char c);
char		*next_word(char *s, char c);
int			count_sep(char *s, char c);
char		*find_path(char *cmd, char **envp);
int			find_path2(char **tab, char *cmd, char **cmd1);
char		*ft_strtrim(char const *s1, char const *set);
int			ft_strchhr(char *envp);
#endif
