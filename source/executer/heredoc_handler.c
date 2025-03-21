/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:24:45 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/21 20:16:09 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	handle_heredocs_pipeline(t_data *data, t_cmd *cmd_lst)
{
	t_cmd			*cmd;
	t_redirection	*redir;
	int				heredoc_index;

	cmd = cmd_lst;
	heredoc_index = 1;
	while (cmd)
	{
		redir = cmd->redirection;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				create_heredoc_file(data, redir, heredoc_index);
				heredoc_index++;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

void	create_and_fill_heredocs(t_data *data, t_redirection *redirection)
{
	t_redirection	*current;
	int				heredoc_index;

	current = redirection;
	heredoc_index = 1;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			create_heredoc_file(data, current, heredoc_index);
			heredoc_index++;
		}
		current = current->next;
	}
}

static void	read_and_write_heredoc(int heredoc_fd, int pipe_fd[2])
{
	char	buffer[1024];
	ssize_t	bytes_read;

	bytes_read = read(heredoc_fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		write(pipe_fd[1], buffer, bytes_read);
		bytes_read = read(heredoc_fd, buffer, sizeof(buffer));
	}
}

static void	transfer_heredocs_to_pipe(t_data *data, t_redirection *redirection,
		int pipe_fd[2])
{
	t_redirection	*current;
	int				heredoc_fd;

	current = redirection;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			heredoc_fd = open(current->file_name, O_RDONLY);
			if (heredoc_fd == -1)
			{
				exit_with_error(data, current->file_name, strerror(errno), 1);
				return ;
			}
			read_and_write_heredoc(heredoc_fd, pipe_fd);
			close(heredoc_fd);
		}
		current = current->next;
	}
}

void	handle_heredocs_simple_cmd(t_data *data, t_redirection *redirection)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		exit_with_error(data, "pipe", strerror(errno), 1);
		return ;
	}
	create_and_fill_heredocs(data, redirection);
	transfer_heredocs_to_pipe(data, redirection, pipe_fd);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		exit_with_error(data, "dup2", strerror(errno), 1);
		close(pipe_fd[0]);
		return ;
	}
	close(pipe_fd[0]);
}
