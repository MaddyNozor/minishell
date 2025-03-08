/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:10:03 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/08 19:06:40 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"
#include <sys/stat.h>  // 🔥 Ajoute cette ligne en haut de ton fichier


void	close_redirections(t_redirection *redirection)
{
	t_redirection	*curr;
	int				fd;

	curr = redirection;
	while (curr)
	{
		fd = open(curr->file_name, O_RDONLY);
		if (fd != -1)
		{
			// printf("🔴 Fermeture de %s (fd: %d)\n", curr->file_name, fd);
			close(fd);
		}
		// else
		// 	printf("⚠️ Impossible d'ouvrir %s pour fermeture\n", curr->file_name);
		curr = curr->next;
	}
}
void	apply_redirections(t_redirection *redirection)// REPRENDRE ICI POUR LES EXTENRES TOUCH,,,,
{
	int	last_output_fd;
	int	input_fd;
	t_redirection *current = redirection;

	last_output_fd = -1;
	input_fd = -1;

	while (current)
	{
		if (current->type == REDIR_IN)
		{
			// printf("🔍 Tentative d'ouverture de %s en mode lecture seule\n", current->file_name);
			input_fd = open(current->file_name, O_RDONLY);
			if (input_fd == -1)
			{
				// printf("Envoye de puis apply redirections :\n");
				// fprintf(stderr, "bash: %s: No such file or directory\n", current->file_name);
				break;
			}
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		current = current->next;
	}
	if (input_fd == -1)
	{
		// printf("⛔ Erreur sur la redirection d'entrée, on annule `>`.\n");
		return;
	}
	handle_output_redirections(redirection, &last_output_fd);
}
