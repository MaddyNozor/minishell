/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:36:45 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/17 17:49:44 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

// void	setup_io_redirections(t_pipe_data *pipe_data, t_cmd *cmd, t_data *data)
// {
// 	int	heredoc_fd;

// 	(void)heredoc_fd;
// 	(void)data;
// 		// printf("🔄 Vérification de STDIN dans setup_io_redirections avant toute redirection\n");

// 	// ✅ Vérification des heredocs avant toute redirection
// 	if (pipe_data->heredoc_fd != -1)
// 	{
// 		// printf("📌 Application du heredoc pour %s\n", cmd->value);
// 		dup2(pipe_data->heredoc_fd, STDIN_FILENO);
// 		close(pipe_data->heredoc_fd);
// 	}
// 	else
// 	{
// 		// printf("✅ Aucun heredoc appliqué pour %s tkt c'est juste un printf on le ire a la fin \n", cmd->value);
// 	}
// 	// ✅ Si ce n'est pas la dernière commande du pipeline, rediriger `STDOUT` vers le pipe
// 	if (cmd->next)
// 	{
// 		dup2(pipe_data->pipe_fd[1], STDOUT_FILENO);
// 	}
// 	// ✅ Fermeture des pipes inutilisés
// 	close(pipe_data->pipe_fd[1]);
// 	close(pipe_data->pipe_fd[0]);
// }


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
