/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:36:45 by sabellil          #+#    #+#             */
/*   Updated: 2025/02/21 14:13:20 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

void	setup_io_redirections(int heredoc_fd, int pipe_in, int pipe_fd[2],
	t_cmd *cmd)
{
	if (heredoc_fd != -1)
	{
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
	else if (pipe_in != 0)
	{
		dup2(pipe_in, STDIN_FILENO);
		close(pipe_in);
	}
	if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	close(pipe_fd[0]);
}

void	read_and_write(int src_fd, int dest_fd)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	bytes_read = read(src_fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		write(dest_fd, buffer, bytes_read);
		bytes_read = read(src_fd, buffer, sizeof(buffer));
	}
}

// void	merge_heredoc_and_input(int heredoc_fd, int input_fd)//avirerapres
// {
// 	int		pipe_fd[2];
// 	char	buffer[1024];
// 	ssize_t	bytes_read;

// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("ERREUR : Echec de la création du pipe");
// 		return ;
// 	}
// 	while ((bytes_read = read(heredoc_fd, buffer, sizeof(buffer))) > 0)
// 		write(pipe_fd[1], buffer, bytes_read);
// 	close(heredoc_fd);
// 	while ((bytes_read = read(input_fd, buffer, sizeof(buffer))) > 0)
// 		write(pipe_fd[1], buffer, bytes_read);
// 	close(input_fd);
// 	close(pipe_fd[1]);
// 	dup2(pipe_fd[0], STDIN_FILENO);
// 	close(pipe_fd[0]);
// }

// void	handle_heredocs(t_redirection *redirection, int *heredoc_fd)
// {
// 	t_redirection	*current;

// 	current = redirection;
// 	while (current)
// 	{
// 		if (current->type == REDIR_HEREDOC)
// 		{
// 			if (access(current->file_name, F_OK) == 0)
// 				*heredoc_fd = open(current->file_name, O_RDONLY);
// 			else
// 			{
// 				if (*heredoc_fd != -1)
// 					close(*heredoc_fd);
// 				*heredoc_fd = ft_create_heredoc(current->file_name);
// 			}
// 		}
// 		current = current->next;
// 	}
// }
