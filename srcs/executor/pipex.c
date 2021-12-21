#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	check_if_builtin(t_cmds cmds, t_builtins *builtins)
{
	int	i;

	i = 0;
	while (builtins[i].builtin)
	{
		if (ft_strcmp(builtins[i].builtin, cmds.cmd))
		{
			builtins[i].fct(cmds);
			return (1);
		}
		i++;
	}
	return (0);
}

void	redir_exec(int fd_in, t_cmds *cmds, int *p, t_cmdline *cmdline)
{
	char	**act;
	char	*path;
	int		fd_out;

	dup2(fd_in, 0);
	if ((*(cmds + 1)).command != NULL)
		dup2(p[1], 1);
	else
	{
		fd_out = 1;
		if (fd_out < 0)
		{
			perror("failed outfile");
			exit(EXIT_FAILURE);
		}
		dup2(fd_out, 1);
	}
	if (close(p[0]) == -1)
		exit(EXIT_FAILURE);
	act = ft_split((*cmds).command, ' ');
	path = find_path(act[0], cmdline->env);
	if (!check_if_builtin(*cmds, cmdline->builtins))
		execve(path, act, NULL);
	exit(EXIT_FAILURE);
}

void	loop_pipe(t_cmdline *cmdline, int fd_in)
{
	pid_t	pid;
	int		p[2];
	t_cmds	*cmds;
	char	**env;

	cmds = cmdline->cmds;
	env = cmdline->env;
	while ((*cmds).command != NULL)
	{
		pipe(p);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
			redir_exec(fd_in, cmds, p, cmdline);
		else
		{
			wait(&cmds->exitstatus);
			printf("%d\n", WEXITSTATUS(cmds->exitstatus));
			if (close(p[1]) == -1)
				exit(EXIT_FAILURE);
			fd_in = p[0];
			cmds++;
		}
	}
}

void	pipex(t_cmdline *cmdline)
{
	int	fd_in;

	fd_in = 0;
	loop_pipe(cmdline, fd_in);
}
