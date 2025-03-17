/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:46:25 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/17 18:24:34 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	handle_output_redirections(t_redirection *redir, int *last_out_fd)
{
	t_redirection	*curr;
	int				flags;

	curr = redir;
	while (curr)
	{
		if (curr->type == REDIRECT_OUT || curr->type == APPEND_OUT)
		{
			if (*last_out_fd != -1)
				close(*last_out_fd);
			flags = O_WRONLY | O_CREAT;
			if (curr->type == REDIRECT_OUT)
				*last_out_fd = open(curr->file_name, flags | O_TRUNC, 0644);
			else if (curr->type == APPEND_OUT)
				*last_out_fd = open(curr->file_name, flags | O_APPEND, 0644);
			if (*last_out_fd == -1)
			{
				perror("ERREUR : Impossible d'ouvrir le fichier de sortie");
				return ;
			}
			// printf("✅ Redirection STDOUT -> %s, FD = %d\n", curr->file_name, *last_out_fd);
			// 🔥 Redirection vers STDOUT
			if (dup2(*last_out_fd, STDOUT_FILENO) == -1)
				perror("ERREUR : dup2 vers STDOUT a échoué");
			close(*last_out_fd);
		}
		curr = curr->next;
	}
}

void	handle_pipe_redirections(t_cmd *cmd, int pipe_in, int pipe_fd[2])
{
	if (pipe_in != 0)
	{
		if (dup2(pipe_in, STDIN_FILENO) == -1)
			perror("Erreur dup2 STDIN");
		close(pipe_in);
	}
	if (cmd->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror("Erreur dup2 STDOUT");
		close(pipe_fd[1]);
	}
	close(pipe_fd[0]);
}

void	handle_heredoc_and_input(int heredoc_fd, int input_fd)
{
	if (heredoc_fd != -1 && input_fd != -1)
		merge_heredoc_and_input(heredoc_fd, input_fd);
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


void merge_heredoc_and_input(int heredoc_fd, int input_fd)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("ERREUR : Echec de la création du pipe");
		return;
	}

	// ✅ Vérifie si heredoc_fd est valide avant de lire
	if (heredoc_fd != -1)
	{
		read_and_write(heredoc_fd, pipe_fd[1]);
		close(heredoc_fd);
	}

	// ✅ Vérifie si input_fd est valide avant de lire
	if (input_fd != -1)
	{
		read_and_write(input_fd, pipe_fd[1]);
		close(input_fd);
	}

	// ✅ Fermeture du côté écriture du pipe
	close(pipe_fd[1]);

	// ✅ Redirige STDIN vers l'entrée du pipe
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("ERREUR : dup2 vers STDIN a échoué");
	}
	close(pipe_fd[0]);
}

void	handle_input_redirection(t_redirection *redirection, int *input_fd,
	t_redirection **last_heredoc, bool *input_redir_found)//OK Mardi 17 aprem
{
t_redirection	*current;

printf("Je rentre dans handle_input_redirection\n");
current = redirection;
while (current)
{
	printf("Je rentre dans la boucle current %i\n", current->type);
	if (current->type == REDIRECT_IN)
	{
		// ✅ Ajout d'un printf pour voir le fichier qu'on tente d'ouvrir
		printf("🔍 Tentative d'ouverture du fichier : %s\n", current->file_name);

		*input_fd = open(current->file_name, O_RDONLY);
		if (*input_fd == -1)
		{
			// ✅ Ajout d'un printf pour signaler que le fichier n'existe pas
			printf("🚨 ERREUR : Le fichier %s n'existe pas !\n", current->file_name);

			// ✅ Affichage de l'erreur immédiatement
			fprintf(stderr, "bash: %s: No such file or directory\n", current->file_name);

				// ✅ Ne pas quitter `minishell`, juste fermer STDIN pour éviter que `cat` ne fonctionne
				close(STDIN_FILENO);
				*input_redir_found = false;
				return;
		}
		else
		{
			printf("✅ Fichier %s ouvert avec succès !\n", current->file_name);
		}
		dup2(*input_fd, STDIN_FILENO);
		close(*input_fd);
		*input_redir_found = true;
	}
	else if (current->type == HEREDOC)
	{
		*last_heredoc = current;
		*input_redir_found = true;
	}
	current = current->next;
}
}

void handle_heredoc_redirection(t_redirection *last_heredoc, int *heredoc_fd)
{
    if (!last_heredoc)
        return;
    // printf("Je suis entré dans handle_heredoc_redirection\n");
    *heredoc_fd = open(last_heredoc->file_name, O_RDONLY);
    if (*heredoc_fd == -1)
    {
        perror("Erreur ouverture heredoc");
        exit(1);
    }
    dup2(*heredoc_fd, STDIN_FILENO);
    close(*heredoc_fd);
}

// void	handle_input_redirection(t_redirection *redirection, int *input_fd,
// 		t_redirection **last_heredoc, bool *input_redir_found)// Ok Mardi 17 matin, mais pas pour cat << EOF << EOF < input.txt | tr 'a-z' 'A-Z' > output.txt
// {
// 	t_redirection	*current;

// 	current = redirection;
// 	while (current)
// 	{
// 		// printf("🔎 Vérification dans handle_input_redirection : type actuel = %d (REDIRECT_IN attendu: %d)\n",
// 		// current->type, REDIRECT_IN);
// 		if (current->type == REDIRECT_IN)
// 		{
// 			// printf("Je suis rentre dnas handle input redirection\n");
// 			// printf("🔍 Tentative d'ouverture de %s en mode lecture seule\n",
// 			// 		current->file_name);
// 			*input_fd = open(current->file_name, O_RDONLY);
// 			if (*input_fd == -1)
// 			{
// 				// printf("Je passe par la verif dans handle_input_process\n");
// 				printf("bash: %s: No such file or directory\n", current->file_name);
// 				*input_redir_found = false;
// 				break ;
// 			}
// 			dup2(*input_fd, STDIN_FILENO);
// 			close(*input_fd);
// 			*input_redir_found = true;
// 		}
// 		else if (current->type == HEREDOC)
// 		{
// 			// printf("Je repere que current type est Heredoc\n");
// 			*last_heredoc = current;
// 		}
// 		// printf("J'arrive vers la fin de handle input redirection, on avance dans current\n");
// 		current = current->next;
// 	}
// 	// printf("J'arrive a la toute fin de handle input redirection\n");
// }
