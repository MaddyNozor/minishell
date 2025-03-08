/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:46:25 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/08 17:49:38 by sabellil         ###   ########.fr       */
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
		if (curr->type == REDIR_OUT || curr->type == REDIR_APPEND)
		{
			if (*last_out_fd != -1)
				close(*last_out_fd);
			flags = O_WRONLY | O_CREAT;
			if (curr->type == REDIR_OUT)
				*last_out_fd = open(curr->file_name, flags | O_TRUNC, 0644);
			else
				*last_out_fd = open(curr->file_name, flags | O_APPEND, 0644);
			if (*last_out_fd == -1)
			{
				perror("ERREUR : Impossible d'ouvrir output.txt");
				return ;
			}
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

// void	handle_input_redirection(t_redirection *redirection,
// 								int *input_fd,
// 								t_redirection **last_heredoc,
// 								bool *input_redir_found)//la base
// {
// 	t_redirection	*current;

// 	current = redirection;
// 	while (current)
// 	{
// 		if (current->type == REDIR_IN)
// 		{
// 			*input_fd = open(current->file_name, O_RDONLY);
// 			if (*input_fd == -1)
// 			{
// 				fprintf(stderr, "bash: %s: No such file or directory\n",
// 					current->file_name);
// 				exit(1);
// 			}
// 			dup2(*input_fd, STDIN_FILENO);
// 			close(*input_fd);
// 			*input_redir_found = true;
// 		}
// 		else if (current->type == REDIR_HEREDOC)
// 			*last_heredoc = current;
// 		current = current->next;
// 	}
// }

void	handle_input_redirection(t_redirection *redirection, int *input_fd,
		t_redirection **last_heredoc, bool *input_redir_found)
{
	t_redirection	*current;

	current = redirection;
	while (current)
	{
		printf("🔎 Vérification dans handle_input_redirection : type actuel = %d (REDIR_IN attendu: %d)\n",
		current->type, REDIR_IN);
		if (current->type == REDIR_IN)
		{
			printf("Je suis rentre dnas handle input redirection\n");
			printf("🔍 Tentative d'ouverture de %s en mode lecture seule\n",
					current->file_name);
			*input_fd = open(current->file_name, O_RDONLY);
			if (*input_fd == -1)
			{
				fprintf(stderr, "bash: %s: No such file or directory\n",
						current->file_name);
				*input_redir_found = false;
				return ;
				// ⏹️ Stoppe immédiatement la fonction et empêche la création de `test1`
			}
			dup2(*input_fd, STDIN_FILENO);
			close(*input_fd);
			*input_redir_found = true;
		}
		else if (current->type == REDIR_HEREDOC)
			*last_heredoc = current;
		current = current->next;
	}
}

void	handle_heredoc_redirection(t_redirection *last_heredoc, int *heredoc_fd)
{
	if (!last_heredoc)
		return ;
	printf("Je suis entré dans handle_heredoc_redirection\n");
	*heredoc_fd = open(last_heredoc->file_name, O_RDONLY);
	if (*heredoc_fd == -1)
	{
		perror("Erreur ouverture heredoc");
		exit(1);
	}
	dup2(*heredoc_fd, STDIN_FILENO);
	close(*heredoc_fd);
	// 🔥 Restaurer l'entrée standard après exécution du heredoc
	int fd_stdin = dup(STDIN_FILENO); // Sauvegarde de STDIN
	dup2(fd_stdin, STDIN_FILENO);     // Restauration de STDIN après execve()
	close(fd_stdin);                 
		// Fermeture du descripteur de fichier temporaire
	printf("✅ STDIN restauré après heredoc.\n");
}
