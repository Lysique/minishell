/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_add_lstfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:14:49 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/17 10:36:10 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_heredoc_string(char *file)
{
	static char	*line_read = (char *) NULL;
	char		*res;
	int			i;
	char		*tmp;

	i = 0;
	res = NULL;
	line_read = readline("heredoc> ");
	while (ft_strcmp(line_read, file) != 0 && line_read)
	{
		if (i++ == 0)
			res = ft_strjoin(line_read, "\n");
		else
		{
			tmp = res;
			res = ft_strjoin(res, line_read);
			free(tmp);
			tmp = res;
			res = ft_strjoin(res, "\n");
			free(tmp);
			free(line_read);
		}
		line_read = readline("heredoc> ");
	}
	return (res);
}

// see https://www.oilshell.org/blog/2016/10/18.html for stacktrace of heredoc
int	ft_heredoc(char *file)
{
	char	*res;
	int		fd;

	res = get_heredoc_string(file);
	fd = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC | O_EXCL, 0600);
	write(fd, res, ft_strlen(res));
	close(fd);
	fd = open("heredoc", O_RDONLY);
	unlink("heredoc");
	return (fd);
}

//O_TRUNC:
//  to reduce size to 0 when opening the file (like what happens in bash)
//  even when nothing is written to the file, if > redir is defined it will 
//	truncate the file to 0

// REVERSE ORDER OF FILES: 
//	we only need to write to the last file defined in the commandline so we push
//	all the others down in the list making it easy to access the one 
//  file we need
t_cmds	add_lst_outfile(t_cmds cmds, char *redirection, char *file)
{
	t_lstfiles	*new;
	t_lstfiles	*listptr;

	new = ft_malloc(sizeof(t_lstfiles), 0);
	listptr = cmds.outfiles;
	if (!redirection[1])
		new->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		new->fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	new->next = listptr;
	cmds.outfiles = new;
	return (cmds);
}

// REVERSE ORDER OF FILES: 
//	we only need to read from the last file defined in the commandline so we 
//  push all the others down in the list making it easy to access the one 
//  file we need
t_cmds	add_lst_infile(t_cmds cmds, char *redirection, char *file)
{
	t_lstfiles	*new;
	t_lstfiles	*listptr;

	new = ft_malloc(sizeof(t_lstfiles), 0);
	listptr = cmds.infiles;
	if (!redirection[1])
		new->fd = open(file, O_RDONLY);
	else
		new->fd = ft_heredoc(file);
	new->next = listptr;
	cmds.infiles = new;
	return (cmds);
}

t_cmds	cmds_add_lstfile(char **arr, t_cmds cmds)
{
	char		*redirection;

	redirection = *arr;
	arr++;
	if (*redirection == '<')
		cmds = add_lst_infile(cmds, redirection, *arr);
	else if (*redirection == '>')
		cmds = add_lst_outfile(cmds, redirection, *arr);
	return (cmds);
}
