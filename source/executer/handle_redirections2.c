/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecole <ecole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:36:45 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/13 18:43:34 by ecole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	setup_io_redirections(t_pipe_data *pipe_data, t_cmd *cmd, t_data *data)
{
	char *cmd_path = find_cmd_path(cmd->value, data->varenv_lst); // Vérification du chemin
	if (!cmd_path)
	{
		printf("bash: %s: command not found\n", cmd->value);
		close(pipe_data->pipe_fd[1]); // 🔴 Fermer la sortie pour éviter un blocage du pipe
		exit(127);
	}
	if (pipe_data->heredoc_fd != -1)
	{
		dup2(pipe_data->heredoc_fd, STDIN_FILENO);
		close(pipe_data->heredoc_fd);
		// printf("✅ HEREDOC redirigé pour %s\n", cmd->value);
	}
	else if (pipe_data->pipe_in != 0)
	{
		dup2(pipe_data->pipe_in, STDIN_FILENO);
		close(pipe_data->pipe_in);
		// printf("✅ STDIN redirigé pour %s\n", cmd->value);
	}
	if (cmd->next)
	{
		dup2(pipe_data->pipe_fd[1], STDOUT_FILENO);
		close(pipe_data->pipe_fd[1]);
		printf("✅ Redirection STDOUT -> Pipe pour %s\n", cmd->value);
	}
	close(pipe_data->pipe_fd[0]);
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
