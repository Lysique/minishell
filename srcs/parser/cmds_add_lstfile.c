/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_add_lstfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:14:49 by tamighi           #+#    #+#             */
/*   Updated: 2022/01/06 04:41:08 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* int	ft_strcmmp(const char *s1, const char *s2)
{
	size_t			i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return ((unsigned char)s2[i]);
	if (!s2)
		return ((unsigned char)s1[i]);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s2[i] == 0 && s2[i - 1] == s1[i - 1])
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
 */
char	*get_heredoc_string(char *file)
{
	static char	*line_read = (char *)NULL;
	char		*res;
	int			i;
	char		*tmp;

	i = 0;
	res = NULL;
	line_read = readline("heredoc> ");
	while (ft_strcmp(line_read, file) != 0 && line_read && *line_read)
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

int	ft_heredoc(char *file)
{
	char	*res;
	int		fd;

	res = get_heredoc_string(file);
	fd = open("fhere.txt",O_CREAT | O_WRONLY, 0777);
	write(fd, res, ft_strlen(res));
	return (0);
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
