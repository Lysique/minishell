/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:03:16 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/08 11:25:57 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_SYNTAX_ERR	258
# define EXIT_CMD_NOT_FOUND_ERR 127

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
# include <dirent.h>
# include <termios.h>
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
	int			exitok;
	int			parentheses;
	int			exitstatus;
	int			pipetype;
	int			fd_out;
	int			fd_in;
	int			p[2];
}				t_cmds;

typedef struct s_cmdline
{
	char				**env;
	struct s_builtins	*builtins;
	t_cmds				*cmds;
	t_array				env_arr;
	char				*line;
	int					exit;
	int					quit;
	pid_t				shellpid;
	char				*prompt;
}			t_cmdline;

typedef struct s_builtins
{
	char	*builtin;
	int		(*fct)(t_cmdline *cmdline);
}				t_builtins;

/*FUNCTIONS*/

t_cmdline	*cl_ptr(t_cmdline *cl);
void		prompt(t_cmdline *cmdline);

void		execute_minishell(char **env);
void		signal_management(void);
void		*ft_malloc(int size, void *p);
char		*check_cmdline(char **arr);

	/*LEXER*/

char		**lexer(char *line);
int			nb_tokens(char *line);
char		**tokens_in_arr(char *line, char **arr);
int			ft_isspace(char c);

	/*PARSER*/

void		parser(char **arr, t_cmdline *cmdline);
void		create_cmdline(char **arr, t_cmdline *cmdline);
t_cmds		cmds_add_lstfile(char **arr, t_cmds cmds);
void		create_command(t_cmdline *cmdline, int nb_cmds);
int			nb_cmds(char **arr);

	/*EXPANDER*/

void		expander(t_cmdline *cmdline);
char		*expand(char *var, t_cmdline *cmdline, int x);
char		*expand_wildcard(char *pattern);
int			env_index(char **env, char *var);
char		*expand_to_env(char *var, char **env, int ix, int i);
char		*fk_quotes(char *var);
char		**expander_split(char *var);

	/*EXECUTOR*/

void		executor(t_cmdline *cmdline);
void		check_exit_status(t_cmdline *cmdline);

	/*BUILTINS*/
int			ft_exit(t_cmdline *cmdline);
int			ft_echo(t_cmdline *cmdline);
int			ft_pwd(t_cmdline *cmdline);
int			ft_cd(t_cmdline *cmdline);
int			ft_env(t_cmdline *cmdline);
int			ft_export(t_cmdline *cmdline);
int			ft_unset(t_cmdline *cmdline);

	/*ENV FUNCTIONS*/
void		env_init(char **envp, t_cmdline *cmdline);
int			has_valid_identifier(char *line);
int			is_nameequword_format(char *name);
int			env_add_var(t_cmdline *cmdline, char *line);
int			env_set_line_at_index(t_cmdline *cmdline, char *linedup,
				int env_index);
int			env_find(t_cmdline *cmdline, char *name);
int			env_set(t_cmdline *cmdline, char *name, char *value);
int			env_unset(t_cmdline *cmdline, char *var_name);
void		free_env(void *arr);
int			ft_strcmp(const char *s1, const char *s2);

/*BONUS*/
	/*
		returns a heap allocated expanded string of all direntries in cwd, matching the pattern as argument
	*/
char		*expand_wildcard(char *pattern);
int			is_match(char *word, char *pattern);
int			is_visible(char *name, char *pattern);

	/*PIPEX*/
void		pipex(t_cmdline *cmdline);
void		redir_exec(t_cmdline *cmdline);
int			check_if_builtin(t_cmdline *cmdline, t_builtins *builtins);
int			miscarriage(t_cmdline *cmdline);
char		**ms_split(char const *s, char c);
char		*find_path(char *cmd, char **envp);

char		*ft_strtrim(char const *s1, char const *set);
int			ft_srch(char *envp, char *var);
int			ft_strequ(char *s1, char *s2);
char		*ms_strjoin(char const *s1, char const *s2);
void		ft_putstr2(char *str);

	/*TERMIOS*/
void		setup_term(void);
void		reset_term(void);

#endif
