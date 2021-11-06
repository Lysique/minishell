/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 09:33:08 by slathouw          #+#    #+#             */
/*   Updated: 2021/11/06 09:29:13 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static void	ft_set_save(char *save[1024], char *text, int fd)
{
	if (save[fd])
	{
		free(save[fd]);
		save[fd] = NULL;
	}
	save[fd] = ft_strdup(text);
	if (text)
	{
		free(text);
		text = NULL;
	}
}

static int	save_read_fd(char *save[1024], int fd)
{
	char	buff[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*swap;

	bytes_read = read(fd, buff, BUFFER_SIZE);
	if (bytes_read)
	{
		buff[bytes_read] = '\0';
		swap = ft_strjoin(save[fd], buff);
		ft_set_save(save, swap, fd);
	}
	return (bytes_read);
}

static char	*get_line(char *save[1024], char *nlptr, int fd)
{
	char	*tmp;
	char	*line;

	if (!nlptr)
	{
		line = ft_strdup(save[fd]);
		if (save[fd])
			free(save[fd]);
		save[fd] = NULL;
		return (line);
	}
	*nlptr = '\0';
	tmp = ft_strdup(save[fd]);
	line = ft_strjoin(tmp, "\n");
	if (tmp)
		free(tmp);
	nlptr = ft_strdup(nlptr + 1);
	ft_set_save(save, nlptr, fd);
	return (line);
}

char	*get_next_line(int fd)
{
	char			testbuff;
	static char		*save[1024];
	int				bytes_saved;
	char			*nlptr;

	if (fd < 0 || (read(fd, &testbuff, 0) < 0 && !ft_strlen(save[fd])))
		return (NULL);
	if (!save[fd])
		save[fd] = ft_strdup("");
	nlptr = ft_strchr(save[fd], '\n');
	while (!nlptr)
	{
		bytes_saved = save_read_fd(save, fd);
		if (!bytes_saved)
			break ;
		nlptr = ft_strchr(save[fd], '\n');
	}
	if (ft_strlen(save[fd]))
		return (get_line(save, nlptr, fd));
	if (save[fd])
	{
		free(save[fd]);
		save[fd] = NULL;
	}
	return (NULL);
}
