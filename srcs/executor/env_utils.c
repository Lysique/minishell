/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 10:56:36 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/27 13:26:01 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_init(char **envp, t_cmdline *cmdline)
{
	char	*line;

	ft_array_init(&cmdline->env_arr, sizeof(char *));
	while (*envp)
	{
		line = ft_strdup(*envp);
		ft_array_add(&cmdline->env_arr, &line);
		envp++;
	}
	ft_array_add(&cmdline->env_arr, 0);
	cmdline->env = cmdline->env_arr.data;
}


int is_nameequword_format(char *line)
{
	char **split;

	if (!ft_strchr(line, '='))
		return (0);
	split = ft_split(line, '=');
	if
}

int is_valid_identifier(char *name)
{
	//if start is NOT numerical and name is NOT number
}

int	env_add_var(t_cmdline *cmdline, char *line)
{
	//TODO: check format = NAME=word
	//TODO: check NAME not exist
	//TODO: add "NAME=word" to env array
}

int env_set_var(t_cmdline *cmdline, char *line)
{
	//TODO: check format = "NAME=word"
	//TODO: check NAME exists
		//IF exists: set line to new line
		//IF not exists: add line to envp
}

char *get_var_value(t_cmdline *cmdline, char *var_name)
{
	//TODO: check if NAME in envp, if it is, return value
}

int env_unset(t_cmdline *cmdline, char *var_name)
{
	
}

int sort_env(t_cmdline *cmdline)
{
	
}