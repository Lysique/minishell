/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_add_lstfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:14:49 by tamighi           #+#    #+#             */
/*   Updated: 2021/12/07 13:51:44 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	end_heredoc(char *line, char *end)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i])
	{
		if (line[i] != end[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_heredoc(char *end)
{
	int		fd;
	char	*line;

	line = readline("< ");
	fd = open("", O_CREAT | O_RDWR);
	while (!end_heredoc(line, end))
	{
		write(fd, line, ft_strlen(line));
		line = readline("< ");
	}
	return (fd);
}

t_cmds	add_lst_outfile(t_cmds cmds, char *redirection, char *file)
{
	t_lstfiles	*new;
	t_lstfiles	*tmp;

	new = ft_malloc(sizeof(t_lstfiles), 0);
	tmp = cmds.outfiles;
	if (!redirection[1])
		new->fd = open(file, O_WRONLY | O_CREAT);
	else
		new->fd = open(file, O_WRONLY | O_CREAT | O_APPEND);
	new->next = 0;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		cmds.outfiles = new;
	else
		tmp->next = new;
	return (cmds);
}

t_cmds	add_lst_infile(t_cmds cmds, char *redirection, char *file)
{
	t_lstfiles	*new;
	t_lstfiles	*tmp;

	new = ft_malloc(sizeof(t_lstfiles), 0);
	tmp = cmds.infiles;
	if (!redirection[1])
		new->fd = open(file, O_RDONLY);
	else
		new->fd = ft_heredoc(file);
	new->next = 0;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		cmds.infiles = new;
	else
		tmp->next = new;
	return (cmds);
}

t_cmds	cmds_add_lstfile(char **arr, t_cmds cmds)
{
	char		*redirection;

	redirection = *arr;
	arr++;
	if (*redirection == '>')
		cmds = add_lst_infile(cmds, redirection, *arr);
	else if (*redirection == '<')
		cmds = add_lst_outfile(cmds, redirection, *arr);
	return (cmds);
}
