/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:55:09 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/21 14:57:21 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_builtins(t_cmdline *cmdline)
{
	t_builtins	builtins[8];
	cmdline->builtins = builtins;
	builtins_init(cmdline);
}

static void	set_up_pipes(int *fds)
{
	pipe(fds);
	pipe(fds + 2);
	fds[4] = dup(0);
	fds[5] = dup(1);
}

static void	switch_pipes_close_files(int *fds, t_cmds *cmd)
{
	close(fds[0]);
	close(fds[1]);
	fds[0] = fds[2];
	fds[1] = fds[3];
	pipe(fds + 2);
	while (cmd->outfiles && cmd->outfiles->fd > 2)
	{
		close(cmd->outfiles->fd);
		cmd->outfiles = cmd->outfiles->next;
	}
	while (cmd->infiles && cmd->infiles->fd > 2)
	{
		close(cmd->infiles->fd);
		cmd->infiles = cmd->infiles->next;
	}
}

static void	wait_if_conditional(t_cmdline *cmdline, t_cmds * current)
{
	if (current->pipetype != 1)
	{
		waitpid(cmdline->is_forked, &cmdline->cmds->exitstatus, 0);
		while (wait(0) != -1)
			;
		check_exit_status(cmdline);
	}
	cmdline->is_forked = 0;
}

void	redir_exec(t_cmdline *cmdline) //TODO: copy to redir_exec.c
{
	char	**act;
	char	*path;

	act = cmdline_to_arr(cmdline);
	path = find_path(act[0], cmdline->env);
	if (!path)
	{
		cmdline->exit = 127;
		exit(EXIT_CMD_NOT_FOUND_ERR);
	}
	execve(path, act, cmdline->env);
}

static void	pipex(t_cmdline *cmdline, int *fds, int flag_in_out[2], t_cmds *current)
{
		int	i;

		if (current->infiles)
				dup2(current->infiles->fd, 0);
		if (current->outfiles)
				dup2(current->outfiles->fd, 1);
		if (miscarriage(cmdline)) //TODO: dup2 in and out files to stdin and stdout AND RESET THEM AFTERWARDS
		{
			dup2(fds[4], 0);
			dup2(fds[5], 1);
			cmdline->cmds->exitok = 1;
			check_exit_status(cmdline);
			return ;
		}
		cmdline->is_forked = fork();
		if (cmdline->is_forked == 0)
		{
			if (flag_in_out[0] && !current->infiles)
				dup2(fds[0], 0);
			if (flag_in_out[1] && !current->outfiles)
				dup2(fds[3], 1);
			i = -1;
			while (++i < 6)
				close(fds[i]);
			redir_exec(cmdline);
		}
		dup2(fds[4], 0);
		dup2(fds[5], 1);
}

void	execute_pipex(t_cmdline *cmdline) //TODO: copy to executor.c
{
	init_builtins(cmdline);
	
	int			fds[6];
	int			i;
	int			flags_in_out[2];
	t_cmds		*current;


	flags_in_out[0] = 0;
	flags_in_out[1] = 0;
	current = cmdline->cmds;
	set_up_pipes(fds);
	while (current->cmd)
	{
		if (current->pipetype == 1)
			flags_in_out[1] = 1;
		cmdline->cmds = current;
		expander(cmdline);
		pipex(cmdline, fds, flags_in_out, current);
		check_for_minishell(current->cmd);
		switch_pipes_close_files(fds, current);
		wait_if_conditional(cmdline, current);
		flags_in_out[0] = flags_in_out[1];
		flags_in_out[1] = 0;
		current++;
	}
	dup2(fds[4], 0);
	dup2(fds[5], 1);
	i = -1;
	while(++i < 6)
		close(fds[i]);
}
