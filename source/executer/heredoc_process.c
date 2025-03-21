/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:20:07 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/21 20:16:45 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static bool	safe_write(t_data *data, int fd, const char *str, size_t len)
{
	if (write(fd, str, len) == -1)
	{
		exit_with_error(data, "write", strerror(errno), 1);
		return (false);
	}
	return (true);
}

void	process_heredoc_input(t_data *data, int fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (!safe_write(data, fd, line, strlen(line))
			|| !safe_write(data, fd, "\n", 1))
		{
			free(line);
			return ;
		}
		free(line);
	}
}
