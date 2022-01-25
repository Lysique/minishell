/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 10:20:52 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/25 12:42:44 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	wait_if_conditional(t_cmdline *cmdline, t_cmds *current)
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

static void	
	pipex(t_cmdline *cmdline, int *fds, int flag_in_out[2], t_cmds *current)
{
	if (current->infiles)
		dup2(current->infiles->fd, 0);
	if (current->outfiles)
		dup2(current->outfiles->fd, 1);
	if (miscarriage(cmdline, flag_in_out))
	{
		restore_stds(fds);
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
		close_fds(fds);
		if (check_if_builtin(cmdline, cmdline->builtins))
			exit(cmdline->exit);
		redir_exec(cmdline);
	}
	restore_stds(fds);
}

void	execute_pipex(t_cmdline *cmdline)
{	
	int			*fds;
	int			flags_in_out[2];
	t_cmds		*current;

	flags_in_out[0] = 0;
	flags_in_out[1] = 0;
	current = cmdline->cmds;
	fds = cmdline->fds;
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
		if ((current->pipetype == 2 && cmdline->exit == 0) 
			|| (current->pipetype == 3 && cmdline->exit != 0))
			break ;
		flags_in_out[0] = flags_in_out[1];
		flags_in_out[1] = 0;
		current++;
	}
	restore_stds(fds);
	close_fds(fds);
}
