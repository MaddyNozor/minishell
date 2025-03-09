/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:10:03 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/09 16:28:36 by sabellil         ###   ########.fr       */
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

void	apply_redirections(t_redirection *redirection)//fonctionne mais pas pour >> 
{
	int				last_output_fd;
	int				input_fd;
	t_redirection	*current;

	last_output_fd = -1;
	input_fd = -1;
	current = redirection;
	while (current)
	{
		if (current->type == REDIRECT_IN)
		{
			// printf("🔍 Tentative d'ouverture de %s en mode lecture seule\n", current->file_name);
			input_fd = open(current->file_name, O_RDONLY);
			if (input_fd == -1)
				break ;
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		current = current->next;
	}
	// current = redirection;
	// while (current)
	// {
	// 	if (current->type == REDIRECT_OUT || current->type == APPEND_OUT)
	// 	{
	// 		printf("🔍 Traitement de la redirection de sortie : %s, type = %d\n",
	// 			   current->file_name, current->type);
	// 	}
	// 	current = current->next;
	// }
	if (input_fd == -1)
	{
		// printf("⛔ Erreur sur la redirection d'entrée, mais on garde `>>`.\n");
		handle_output_redirections(redirection, &last_output_fd);
		return ;
	}
	handle_output_redirections(redirection, &last_output_fd);
}
