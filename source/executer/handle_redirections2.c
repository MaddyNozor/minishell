/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:36:45 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/21 20:16:01 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	read_and_write(t_data *data, int src_fd, int dest_fd)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	bytes_read = read(src_fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		if (write(dest_fd, buffer, bytes_read) == -1)
		{
			perror("ERREUR : Echec de l'écriture");
			update_exit_status(data, 1);
			break ;
		}
		bytes_read = read(src_fd, buffer, sizeof(buffer));
	}
	close(dest_fd);
}

void	handle_heredoc_and_input(t_data *data, int heredoc_fd, int input_fd)
{
	if (heredoc_fd != -1 && input_fd != -1)
		merge_heredoc_and_input(data, heredoc_fd, input_fd);
	else if (heredoc_fd != -1)
	{
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
	else if (input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
}

void	merge_heredoc_and_input(t_data *data, int heredoc_fd, int input_fd)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("ERREUR : pipe a échoué");
		update_exit_status(data, 1);
		return ;
	}
	if (heredoc_fd != -1)
	{
		read_and_write(data, heredoc_fd, pipe_fd[1]);
		close(heredoc_fd);
	}
	if (input_fd != -1)
	{
		read_and_write(data, input_fd, pipe_fd[1]);
		close(input_fd);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("ERREUR : dup2 vers STDIN a échoué");
		update_exit_status(data, 1);
	}
	close(pipe_fd[0]);
}

void	handle_heredoc_redirection(t_data *data, t_redirection *last_heredoc,
		int *heredoc_fd)
{
	if (!last_heredoc)
		return ;
	*heredoc_fd = open(last_heredoc->file_name, O_RDONLY);
	if (*heredoc_fd == -1)
	{
		exit_with_error(data, last_heredoc->file_name,
			"Erreur ouverture heredoc", 1);
		return ;
	}
	dup2(*heredoc_fd, STDIN_FILENO);
	close(*heredoc_fd);
}
