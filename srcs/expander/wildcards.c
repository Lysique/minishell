/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:32:18 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/03 12:04:26 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_strjoinfree(char *dest, const char *str)
{
	char	*tmp;

	tmp = ft_strjoin(dest, str);
	free(dest);
	dest = tmp;
	return (dest);
}

char	*get_matches_in_dir(DIR *dir, char *pattern)
{
	struct dirent	*entry;
	char			*concat;
	int				count;

	count = 0;
	entry = readdir(dir);
	concat = ft_strdup("");
	while (entry)
	{
		if (is_match(entry->d_name, pattern)
			&& is_visible(entry->d_name, pattern))
		{
			if (count)
				concat = ft_strjoinfree(concat, " ");
			count++;
			concat = ft_strjoinfree(concat, entry->d_name);
		}
		entry = readdir(dir);
	}
	return (concat);
}

char	*expand_wildcard(char *pattern)
{
	char	*curr_dir_path;
	char	*ret;
	DIR		*curr_dir;

	curr_dir_path = getcwd(NULL, 0);
	//TODO: if expansion fails->write error "minishell: No matches found: <format>"
	curr_dir = opendir(curr_dir_path);
	ret = get_matches_in_dir(curr_dir, pattern);
	closedir(curr_dir);
	return (ret);
}

int	ft_expand(t_cmdline *cmdline)
{
	t_args	*args;

	args = cmdline->cmds->args;
	while (args)
	{
		ft_printf("EXPANDER:\n");
		ft_printf("wildarg = |%s|\nexpanded to = |%s|\n",
			(char *) args->content, expand_wildcard((char *)args->content));
		args = args->next;
	}
	return (1);
}
