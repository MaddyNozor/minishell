/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:10:03 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/17 14:04:29 by sabellil         ###   ########.fr       */
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

void	apply_redirections(t_redirection *redirection)
{
	int				last_output_fd;
	int				input_fd;
	t_redirection	*current;
	t_redirection	*last_heredoc;
	bool			input_redir_found = true;
	bool			output_created = false;

	last_output_fd = -1;
	input_fd = -1;
	last_heredoc = NULL;
	current = redirection;
	printf("Je rentre dans apply_redirections\n");

	// ✅ Étape 1 : Lire et stocker les heredocs, MAIS NE PAS LES APPLIQUER IMMÉDIATEMENT
	while (current)
	{
		if (current->type == HEREDOC)
			last_heredoc = current;
		current = current->next;
	}

	// ✅ Étape 2 : Vérifier si < input.txt existe après lecture des heredocs
	current = redirection;
	while (current)
	{
		if (current->type == REDIRECT_IN)
		{
			input_fd = open(current->file_name, O_RDONLY);
			if (input_fd == -1)
			{
				// ✅ Étape 2.1 : CRÉER output.txt avant de stopper (comme Bash)
				t_redirection *out = redirection;
				while (out)
				{
					if ((out->type == REDIRECT_OUT || out->type == APPEND_OUT) && !output_created)
					{
						int fd = open(out->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
						if (fd != -1)
							close(fd);
						output_created = true;
					}
					out = out->next;
				}

				// ✅ Étape 2.2 : Afficher l'erreur et STOPPER tout (aucune exécution de `cat`)
				fprintf(stderr, "bash: %s: No such file or directory\n", current->file_name);
				exit(1);
			}
			close(input_fd);
		}
		current = current->next;
	}
	printf("Je suis juste avant handle_input_redirection\n");

	// ✅ Étape 3 : Appliquer les redirections seulement si input.txt est valide
	handle_input_redirection(redirection, &input_fd, &last_heredoc, &input_redir_found);
	if (!input_redir_found)
		return;

	if (last_heredoc)
		handle_heredoc_redirection(last_heredoc, &input_fd);

	handle_output_redirections(redirection, &last_output_fd);
}



// void	apply_redirections(t_redirection *redirection)//ok pour Mardi 17 matin
// {
// 	int				last_output_fd;
// 	int				input_fd;
// 	t_redirection	*current;
// 	t_redirection	*last_heredoc;
// 	bool			input_redir_found = true;

// 	last_output_fd = -1;
// 	input_fd = -1;
// 	last_heredoc = NULL;
// 	current = redirection;

// 	// printf("Je suis dans apply_redirections\n");
// 	while (current)
// 	{
// 		// printf("🔍 Recherche du dernier heredoc : type = %d, fichier = %s\n",
// 		//        current->type, current->file_name);
// 		if (current->type == HEREDOC)
// 			last_heredoc = current;
// 		current = current->next;
// 	}
	
// 	// printf("J'entre dans handle_input_redirection\n");
// 	handle_input_redirection(redirection, &input_fd, &last_heredoc, &input_redir_found);
// 	// printf("Je ressors de handle_input_redirection\n");
	
// 	if (!input_redir_found)
// 	{
// 		// printf("🚨 Aucune entrée valide trouvée, sortie de apply_redirections\n");
// 		return;
// 	}

// 	// printf("Je m'apprête à vérifier la redirection heredoc\n");
// 	if (last_heredoc)
// 	{
// 		// printf("✅ Traitement du heredoc : fichier = %s\n", last_heredoc->file_name);
// 		handle_heredoc_redirection(last_heredoc, &input_fd);
// 	}

// 	current = redirection;
// 	while (current)
// 	{
// 		// printf("🔍 Traitement de la redirection : type = %d, fichier = %s\n",
// 		//        current->type, current->file_name);

// 		if (current->type == REDIRECT_IN)
// 		{
// 			// printf("📥 Redirection d'entrée depuis %s\n", current->file_name);
// 			input_fd = open(current->file_name, O_RDONLY);
// 			if (input_fd == -1)
// 			{
// 				// printf("❌ Erreur d'ouverture de %s\n", current->file_name);
// 				break;
// 			}
// 			dup2(input_fd, STDIN_FILENO);
// 			close(input_fd);
// 		}
// 		current = current->next;
// 	}
// 	if (input_fd == -1)
// 	{
// 		// printf("⚠️ Aucun fichier d'entrée ouvert, on passe aux redirections de sortie\n");
// 		handle_output_redirections(redirection, &last_output_fd);
// 		return;
// 	}
// 	// printf("🔄 Application des redirections de sortie\n");
// 	handle_output_redirections(redirection, &last_output_fd);
// }
