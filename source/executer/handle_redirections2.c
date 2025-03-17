/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:36:45 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/17 14:34:50 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	setup_io_redirections(t_pipe_data *pipe_data, t_cmd *cmd, t_data *data)
{
	int	heredoc_fd;

	(void)heredoc_fd;
	(void)data;
		printf("🔄 Vérification de STDIN dans setup_io_redirections avant toute redirection\n");

	// ✅ Vérification des heredocs avant toute redirection
	if (pipe_data->heredoc_fd != -1)
	{
		// printf("📌 Application du heredoc pour %s\n", cmd->value);
		dup2(pipe_data->heredoc_fd, STDIN_FILENO);
		close(pipe_data->heredoc_fd);
	}
	else
	{
		printf("✅ Aucun heredoc appliqué pour %s\n", cmd->value);
	}

	// ✅ Si ce n'est pas la dernière commande du pipeline, rediriger `STDOUT` vers le pipe
	if (cmd->next)
	{
		dup2(pipe_data->pipe_fd[1], STDOUT_FILENO);
	}

	// ✅ Fermeture des pipes inutilisés
	close(pipe_data->pipe_fd[1]);
	close(pipe_data->pipe_fd[0]);
}

// void	setup_io_redirections(t_pipe_data *pipe_data, t_cmd *cmd, t_data *data)
// {
// 	// int	heredoc_fd;

// 	(void)cmd;
// 	(void)data;

// 	printf("🔄 Vérification de STDIN dans setup_io_redirections avant toute redirection\n");

// 	// ✅ Vérification de ce que contient STDIN avant toute redirection
// 	char buffer[1024];
// 	ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
// 	if (bytes_read > 0)
// 	{
// 		buffer[bytes_read] = '\0';
// 		printf("📥 Contenu dans STDIN à ce stade :\n%s\n", buffer);
// 	}
// 	else
// 	{
// 		printf("⚠️ Aucune donnée dans STDIN à ce stade\n");
// 	}

// 	// ❌ Empêcher `heredoc` d'écraser `STDIN` si `< input.txt>` a été appliqué
// 	if (pipe_data->heredoc_fd != -1 && isatty(STDIN_FILENO))
// 	{
// 		printf("📌 Application du heredoc car aucun fichier d'entrée n'a été appliqué\n");
// 		dup2(pipe_data->heredoc_fd, STDIN_FILENO);
// 		close(pipe_data->heredoc_fd);
// 	}
// 	else
// 	{
// 		printf("✅ Aucun heredoc appliqué car `< input.txt>` est déjà en place\n");
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


// void	setup_io_redirections(t_pipe_data *pipe_data, t_cmd *cmd, t_data *data)//Mardi 17 matin
// {
// 	char *cmd_path = find_cmd_path(cmd->value, data->varenv_lst);
// 	if (!cmd_path)
// 	{
// 		printf("bash: %s: command not found\n", cmd->value);
// 		close(pipe_data->pipe_fd[1]);
// 		exit(127);
// 	}

// 	if (pipe_data->heredoc_fd != -1)
// 	{
// 		dup2(pipe_data->heredoc_fd, STDIN_FILENO);
// 		close(pipe_data->heredoc_fd);
// 	}
// 	else if (pipe_data->pipe_in != 0)
// 	{
// 		dup2(pipe_data->pipe_in, STDIN_FILENO);
// 		close(pipe_data->pipe_in);
// 	}

// 	// ✅ Fermer `stdout` seulement pour les commandes finales (ex: `echo`, `ls`)
// 	if (cmd->next)
// 	{
// 		dup2(pipe_data->pipe_fd[1], STDOUT_FILENO);
// 		close(pipe_data->pipe_fd[1]);
// 	}
// 	else
// 	{
// 		close(pipe_data->pipe_fd[1]); // 🔴 Ferme la sortie pour empêcher une boucle infinie
// 	}

// 	close(pipe_data->pipe_fd[0]); // Fermer l’entrée du pipe

// 	// ✅ Assurer que `cat` reste ouvert
// 	if (ft_strcmp(cmd->value, "cat") == 0 && cmd->next == NULL)
// 	{
// 		// On ne ferme pas stdin, sinon `cat` se termine tout seul
// 	}
// }

// void	setup_io_redirections(t_pipe_data *pipe_data, t_cmd *cmd, t_data *data)//ca fonctionne mais ne gere pas pb de cat | cat | ls
// {
// 	char *cmd_path = find_cmd_path(cmd->value, data->varenv_lst); // Vérification du chemin
// 	if (!cmd_path)
// 	{
// 		printf("bash: %s: command not found\n", cmd->value);
// 		close(pipe_data->pipe_fd[1]); // 🔴 Fermer la sortie pour éviter un blocage du pipe
// 		exit(127);
// 	}
// 	if (pipe_data->heredoc_fd != -1)
// 	{
// 		dup2(pipe_data->heredoc_fd, STDIN_FILENO);
// 		close(pipe_data->heredoc_fd);
// 		// printf("✅ HEREDOC redirigé pour %s\n", cmd->value);
// 	}
// 	else if (pipe_data->pipe_in != 0)
// 	{
// 		dup2(pipe_data->pipe_in, STDIN_FILENO);
// 		close(pipe_data->pipe_in);
// 		// printf("✅ STDIN redirigé pour %s\n", cmd->value);
// 	}
// 	if (cmd->next)
// 	{
// 		dup2(pipe_data->pipe_fd[1], STDOUT_FILENO);
// 		close(pipe_data->pipe_fd[1]);
// 		// printf("✅ Redirection STDOUT -> Pipe pour %s\n", cmd->value); //PS on passe par la pour ls | cat | cat
// 	}
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
