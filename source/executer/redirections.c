/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:10:03 by sabellil          #+#    #+#             */
/*   Updated: 2025/02/21 13:47:11 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	close_redirections(t_redirection *redirection)
{
	t_redirection	*curr;
	int				fd;

	curr = redirection;
	while (curr)
	{
		if (curr->type == REDIR_IN
			|| curr->type == REDIR_OUT
			|| curr->type == REDIR_APPEND
			|| curr->type == REDIR_HEREDOC)
		{
			fd = open(curr->file_name, O_RDONLY);
			if (fd != -1)
			{
				close(fd);
				printf("✅ Fichier %s fermé avec succès\n", curr->file_name);
			}
			else
				printf("❌ Impossible d'ouvrir %s pour fermeture\n",
					curr->file_name);
		}
		curr = curr->next;
	}
	if (dup2(STDIN_FILENO, STDIN_FILENO) != -1)
		close(STDIN_FILENO);
}

void	apply_redirections(t_redirection *redirection)
{
	int				last_output_fd;
	int				heredoc_fd;
	int				input_fd;
	t_redirection	*last_heredoc;
	bool			input_redir_found;

	last_output_fd = -1;
	heredoc_fd = -1;
	input_fd = -1;
	last_heredoc = NULL;
	input_redir_found = false;
	handle_output_redirections(redirection, &last_output_fd);
	handle_input_redirection(redirection, &input_fd, &last_heredoc,
		&input_redir_found);
	if (!input_redir_found)
		handle_heredoc_redirection(last_heredoc, &heredoc_fd);
	if (last_output_fd != -1)
	{
		dup2(last_output_fd, STDOUT_FILENO);
		close(last_output_fd);
	}
}
