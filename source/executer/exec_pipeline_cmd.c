/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:04:30 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/17 14:45:08 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"


void	execute_external_cmd(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;
	char	**env_array;

	// ✅ Vérifier si `execve()` est bien appelé avec les bons arguments
	// printf("📌 Vérification de `execve()` pour %s\n", cmd->value);
	// printf("🔹 Commande complète : ");
	for (int i = 0; cmd->argv[i] != NULL; i++)
	{
		printf("%s ", cmd->argv[i]);
	}
	printf("\n");

	// ✅ Supprimer les logs avant `execve()` pour éviter qu’ils ne soient écrits dans `output.txt`
	fflush(stdout);
	fflush(stderr);

	// ✅ Exécution du programme
	cmd_path = find_cmd_path(cmd->value, data->varenv_lst);
	if (!cmd_path || access(cmd_path, X_OK) == -1)
	{
		fprintf(stderr, "bash: %s: command not found\n", cmd->value);
		free(cmd_path);
		exit(127);
	}
	env_array = convert_env_list_to_array(data->varenv_lst);
	if (!env_array)
	{
		perror("env conversion failed");
		free(cmd_path);
		exit(127);
	}
	execve(cmd_path, cmd->argv, env_array);
	perror("execve failed");
	free(cmd_path);
	free_tab(env_array);
	exit(127);
}

// void	execute_external_cmd(t_cmd *cmd, t_data *data)
// {
// 	char	*cmd_path;
// 	char	**env_array;
// 	char	buffer[1024];
// 	ssize_t	bytes_read;

// 	// ✅ Vérifier si `STDIN` est bien positionné avant execve
// 	printf("📌 Vérification de STDIN avant execve pour %s\n", cmd->value);
// 	bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
// 	if (bytes_read > 0)
// 	{
// 		buffer[bytes_read] = '\0';
// 		printf("📥 Contenu reçu sur STDIN :\n%s\n", buffer);
// 	}
// 	else
// 	{
// 		printf("⚠️ Aucune donnée reçue sur STDIN pour %s\n", cmd->value);
// 	}

// 	// ✅ Exécution du programme
// 	cmd_path = find_cmd_path(cmd->value, data->varenv_lst);
// 	if (!cmd_path || access(cmd_path, X_OK) == -1)
// 	{
// 		printf("bash: %s: command not found\n", cmd->value);
// 		free(cmd_path);
// 		exit(127);
// 	}
// 	env_array = convert_env_list_to_array(data->varenv_lst);
// 	if (!env_array)
// 	{
// 		perror("env conversion failed");
// 		free(cmd_path);
// 		exit(127);
// 	}
// 	execve(cmd_path, cmd->argv, env_array);
// 	perror("execve failed");
// 	free(cmd_path);
// 	free_tab(env_array);
// 	exit(127);
// }

// void	execute_external_cmd(t_cmd *cmd, t_data *data)
// {
// 	char	*cmd_path;
// 	char	**env_array;

// 	// printf("On passe par la fonction execute_external_cmd\n");
// 	cmd_path = find_cmd_path(cmd->value, data->varenv_lst);
// 	if (!cmd_path || access(cmd_path, X_OK) == -1)
// 	{
// 		printf("bash: %s: command not found\n", cmd->value);
// 		free(cmd_path);
// 		exit(127);
// 	}
// 	env_array = convert_env_list_to_array(data->varenv_lst);
// 	if (!env_array)
// 	{
// 		perror("env conversion failed");
// 		free(cmd_path);
// 		exit(127);
// 	}
// 	// printf("🚀 Avant execve(), est-ce que %s existe ? %d\n",
//     //    cmd->argv[1], access(cmd->argv[1], F_OK) == 0);
// 	// printf("🔍 Vérification après heredoc : commande reçue = %s\n", cmd->value);
// 	execve(cmd_path, cmd->argv, env_array);
// 	perror("execve failed");
// 	free(cmd_path);
// 	free_tab(env_array);
// 	exit(127);
// }




// void	handle_child_process_pipeline(t_cmd *cmd, t_data *data, int pipe_in, int pipe_fd[2])//OK pour cat << EOF << EOF < input.txt | tr 'a-z' 'A-Z' > output.txt
// {
// 	// int		input_fd;
// 	int		output_fd = -1;
// 	t_pipe_data pipe_data;
// 	// char	buffer[1024];
// 	// ssize_t	bytes_read;

// 	pipe_data.heredoc_fd = -1;
// 	setup_heredoc_fd(cmd, &pipe_data.heredoc_fd);
// 	pipe_data.pipe_in = pipe_in;
// 	pipe_data.pipe_fd[0] = pipe_fd[0];
// 	pipe_data.pipe_fd[1] = pipe_fd[1];

// 	printf("📌 Entrée dans handle_child_process_pipeline pour %s\n", cmd->value);

// 	// ✅ Vérifier si STDIN est un pipe ou un heredoc
// 	if (pipe_in != 0)
// 	{
// 		printf("🔄 Redirection de STDIN vers le pipe pour %s\n", cmd->value);
// 		dup2(pipe_in, STDIN_FILENO);
// 		close(pipe_in);
// 	}
// 	else if (pipe_data.heredoc_fd != -1)
// 	{
// 		printf("📌 Application du heredoc pour %s\n", cmd->value);
// 		dup2(pipe_data.heredoc_fd, STDIN_FILENO);
// 		close(pipe_data.heredoc_fd);
// 	}

// 	// ✅ Vérifier si STDOUT doit être redirigé vers output.txt
// 	t_redirection *redir = cmd->redirection;
// 	while (redir)
// 	{
// 		if (redir->type == REDIRECT_OUT)
// 		{
// 			// ✅ Ouvrir output.txt en mode écriture et rediriger STDOUT vers ce fichier
// 			output_fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (output_fd == -1)
// 			{
// 				perror("Erreur ouverture output.txt");
// 				exit(1);
// 			}
// 			printf("🔄 Redirection de STDOUT vers %s\n", redir->file_name);
// 			dup2(output_fd, STDOUT_FILENO);
// 			close(output_fd);
// 		}
// 		redir = redir->next;
// 	}

// 	// ✅ Fermer pipe_fd[1] si ce n’est pas la dernière commande
// 	if (cmd->next)
// 	{
// 		printf("🔄 Redirection de STDOUT vers le pipe\n");
// 		dup2(pipe_fd[1], STDOUT_FILENO);
// 		close(pipe_fd[1]);
// 	}

// 	// ✅ Fermer pipe_fd[0] uniquement après exécution
// 	close(pipe_fd[0]);

// 	// ✅ Exécuter la commande
// 	if (is_builtin(cmd->value))
// 	{
// 		execute_builtin(cmd, data);
// 		exit(0);
// 	}
// 	execute_external_cmd(cmd, data);
// 	perror("execve failed");
// 	exit(127);
// }


void	handle_child_process_pipeline(t_cmd *cmd, t_data *data, int pipe_in, int pipe_fd[2])//Mardi 17 Matin OK pour cat << EOF1 << EOF2 | lssss | tr 'a-z' 'A-Z' | rev << EOF3 << EOF4 
{
	int		input_fd;
	char	*cmd_path;
	t_pipe_data pipe_data;

	pipe_data.heredoc_fd = -1;
	setup_heredoc_fd(cmd, &pipe_data.heredoc_fd);
	pipe_data.pipe_in = pipe_in;
	pipe_data.pipe_fd[0] = pipe_fd[0];
	pipe_data.pipe_fd[1] = pipe_fd[1];
	setup_io_redirections(&pipe_data, cmd, data);

	cmd_path = find_cmd_path(cmd->value, data->varenv_lst);
	if (!cmd_path)
	{
		printf("bash: %s: command not found\n", cmd->value);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			exit(127);
		}
		exit(127);
	}
	if (is_builtin(cmd->value))
	{
		input_fd = open(cmd->redirection->file_name, O_RDONLY);
		if (input_fd == -1)
		{
			printf("bash: %s: No such file or directory\n", cmd->redirection->file_name);
			exit(1);
		}
		execute_builtin(cmd, data);
		exit(0);
	}
	execute_external_cmd(cmd, data);
	perror("execve failed");
	exit(127);
} 



void	handle_parent_process_pipeline(pid_t pid, t_cmd *cmd, int *pipe_in, int pipe_fd[2])
{
	int	status;

	printf("📌 Entrée dans handle_parent_process_pipeline pour %s\n", cmd->value);

	waitpid(pid, &status, 0);

	// ✅ Vérifier si on ferme `pipe_fd[0]` trop tôt
	if (*pipe_in != 0)
	{
		printf("⚠️ Fermeture de pipe_in (%d) pour %s\n", *pipe_in, cmd->value);
		close(*pipe_in);
	}
	else
	{
		printf("✅ `pipe_in` reste ouvert pour %s\n", cmd->value);
	}

	// ✅ On transmet l'entrée au prochain processus
	*pipe_in = pipe_fd[0]; 

	// ✅ Fermer la sortie du pipe
	close(pipe_fd[1]);
}

// void	handle_parent_process_pipeline(pid_t pid, t_cmd *cmd, int *pipe_in, int pipe_fd[2])
// {
// 	(void)cmd;
// 	(void)pid;
// 	close(pipe_fd[1]);
// 	if (*pipe_in != 0)
// 		close(*pipe_in);
// 	*pipe_in = pipe_fd[0]; // Préparer la prochaine commande à lire depuis ce pipe
// }




// void	execute_pipeline_command(t_cmd *cmd, t_data *data, int *pipe_in,
// 		int pipe_fd[2])
// {
// 	pid_t	pid;

// 	setup_pipe(pipe_fd);
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("Erreur lors du fork");
// 		exit(1);
// 	}
// 	if (pid == 0)
// 	{
// 		// printf("Avant d'entrer dans child process Je traite la commande %s\n", cmd->value);
// 		handle_child_process_pipeline(cmd, data, *pipe_in, pipe_fd);
// 	}
// 	else
// 		handle_parent_process_pipeline(pid, cmd, pipe_in, pipe_fd);
// }

void	execute_pipeline_command(t_cmd *cmd, t_data *data, int *pipe_in,
	int pipe_fd[2])
{
pid_t	pid;
int		input_fd;
bool	input_exists = true;

printf("📌 Entrée dans execute_pipeline_command pour %s\n", cmd->value);

// ✅ Vérifier si `< input.txt>` existe avant le fork
if (cmd->redirection)
{
	t_redirection *redir = cmd->redirection;
	while (redir)
	{
		if (redir->type == REDIRECT_IN)
		{
			printf("🔍 Vérification du fichier d'entrée : %s\n", redir->file_name);
			input_fd = open(redir->file_name, O_RDONLY);
			if (input_fd == -1)
			{
				printf("🚨 ERREUR : Le fichier %s n'existe pas !\n", redir->file_name);
				fprintf(stderr, "bash: %s: No such file or directory\n", redir->file_name);
				input_exists = false;
			}
			else
			{
				printf("✅ Fichier %s ouvert avec succès !\n", redir->file_name);
				close(input_fd);
			}
		}
		redir = redir->next;
	}
}

// ✅ Toujours créer `output.txt`
t_redirection *out = cmd->redirection;
while (out)
{
	if (out->type == REDIRECT_OUT || out->type == APPEND_OUT)
	{
		int fd = open(out->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd != -1)
			close(fd);
	}
	out = out->next;
}

// ❌ Ne pas forker `cat` si `input.txt` n'existe pas
if (!input_exists)
{
	printf("⚠️ Le pipeline continue, mais `%s` ne sera pas exécutée.\n", cmd->value);
	int devnull_fd = open("/dev/null", O_RDONLY);
	if (devnull_fd != -1)
		dup2(devnull_fd, STDIN_FILENO);
	return;
}

// ✅ Création du processus enfant
setup_pipe(pipe_fd);
pid = fork();
if (pid == -1)
{
	perror("Erreur lors du fork");
	exit(1);
}
if (pid == 0)
{
	handle_child_process_pipeline(cmd, data, *pipe_in, pipe_fd);
}
else
{
	handle_parent_process_pipeline(pid, cmd, pipe_in, pipe_fd);
}
}


// void	execute_pipeline_command(t_cmd *cmd, t_data *data, int *pipe_in,
// 	int pipe_fd[2])// OK Lundi 17 aprem 
// {
// pid_t	pid;
// int		input_fd;
// bool	input_exists = true; // ✅ Variable pour savoir si l'entrée existe

// // ✅ Vérifier si `< input.txt>` existe avant de créer un processus
// if (cmd->redirection)
// {
// 	t_redirection *redir = cmd->redirection;
// 	while (redir)
// 	{
// 		if (redir->type == REDIRECT_IN)
// 		{
// 			printf("🔍 Vérification du fichier d'entrée : %s\n", redir->file_name);
// 			input_fd = open(redir->file_name, O_RDONLY);
// 			if (input_fd == -1)
// 			{
// 				printf("🚨 ERREUR : Le fichier %s n'existe pas !\n", redir->file_name);
// 				fprintf(stderr, "bash: %s: No such file or directory\n", redir->file_name);
// 				input_exists = false; // ❌ On marque que l'entrée n'existe pas
// 			}
// 			else
// 				close(input_fd);
// 		}
// 		redir = redir->next;
// 	}
// }

// // ✅ Toujours créer `output.txt` même si `input.txt` n'existe pas
// t_redirection *out = cmd->redirection;
// while (out)
// {
// 	if (out->type == REDIRECT_OUT || out->type == APPEND_OUT)
// 	{
// 		int fd = open(out->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd != -1)
// 			close(fd);
// 	}
// 	out = out->next;
// }

// // ❌ Ne pas créer un processus pour `cat` si `input.txt` est absent
// if (!input_exists)
// {
// 	printf("⚠️ Le pipeline continue, mais la commande `%s` ne sera pas exécutée.\n", cmd->value);

// 	// ✅ Rediriger `STDIN` vers `/dev/null` au lieu de le fermer
// 	int devnull_fd = open("/dev/null", O_RDONLY);
// 	if (devnull_fd != -1)
// 		dup2(devnull_fd, STDIN_FILENO);

// 	return; // ❌ On ne fait pas de `fork()`
// }

// // ✅ Création du pipe et du processus enfant
// setup_pipe(pipe_fd);
// pid = fork();
// if (pid == -1)
// {
// 	perror("Erreur lors du fork");
// 	exit(1);
// }
// if (pid == 0)
// {
// 	// Processus enfant
// 	handle_child_process_pipeline(cmd, data, *pipe_in, pipe_fd);
// }
// else
// {
// 	// Processus parent
// 	handle_parent_process_pipeline(pid, cmd, pipe_in, pipe_fd);
// }
// }



// void	execute_pipeline_command(t_cmd *cmd, t_data *data, int *pipe_in,
// 	int pipe_fd[2])
// {
// pid_t	pid;
// int		input_fd;

// // ✅ Vérifier AVANT `fork()` si `< input.txt>` existe
// if (cmd->redirection)
// {
// 	t_redirection *redir = cmd->redirection;
// 	while (redir)
// 	{
// 		if (redir->type == REDIRECT_IN)
// 		{
// 			// printf("🔍 Vérification du fichier d'entrée : %s\n", redir->file_name);
// 			input_fd = open(redir->file_name, O_RDONLY);
// 			if (input_fd == -1)
// 			{
// 				// printf("🚨 ERREUR : Le fichier %s n'existe pas !\n", redir->file_name);
// 				fprintf(stderr, "bash: %s: No such file or directory\n", redir->file_name);
// 				exit(1); // ⛔ STOP immédiatement avant le fork !
// 			}
// 			close(input_fd);
// 		}
// 		redir = redir->next;
// 	}
// }

// // ✅ Création du pipe après validation des entrées
// setup_pipe(pipe_fd);
// pid = fork();
// if (pid == -1)
// {
// 	perror("Erreur lors du fork");
// 	exit(1);
// }
// if (pid == 0)
// {
// 	// Processus enfant
// 	handle_child_process_pipeline(cmd, data, *pipe_in, pipe_fd);
// }
// else
// {
// 	// Processus parent
// 	handle_parent_process_pipeline(pid, cmd, pipe_in, pipe_fd);
// }
// }

// void	execute_pipeline_command(t_cmd *cmd, t_data *data, int *pipe_in,
// 	int pipe_fd[2])//OK mais execute quand meme le cat 
// {
// pid_t	pid;
// int		input_fd;
// bool	input_exists = true; // ✅ Variable pour savoir si l'entrée existe

// // ✅ Vérifier si `< input.txt>` existe avant de créer un processus
// if (cmd->redirection)
// {
// 	t_redirection *redir = cmd->redirection;
// 	while (redir)
// 	{
// 		if (redir->type == REDIRECT_IN)
// 		{
// 			printf("🔍 Vérification du fichier d'entrée : %s\n", redir->file_name);
// 			input_fd = open(redir->file_name, O_RDONLY);
// 			if (input_fd == -1)
// 			{
// 				printf("🚨 ERREUR : Le fichier %s n'existe pas !\n", redir->file_name);
// 				fprintf(stderr, "bash: %s: No such file or directory\n", redir->file_name);
// 				input_exists = false; // ❌ On marque que l'entrée n'existe pas
// 			}
// 			else
// 				close(input_fd);
// 		}
// 		redir = redir->next;
// 	}
// }

// // ✅ Toujours créer `output.txt` même si `input.txt` n'existe pas
// t_redirection *out = cmd->redirection;
// while (out)
// {
// 	if (out->type == REDIRECT_OUT || out->type == APPEND_OUT)
// 	{
// 		int fd = open(out->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd != -1)
// 			close(fd);
// 	}
// 	out = out->next;
// }

// // ❌ Ne pas créer un processus si `input.txt` est manquant
// if (!input_exists)
// {
// 	printf("⚠️ Le pipeline continue, mais la commande `%s` ne sera pas exécutée.\n", cmd->value);
// 	return;
// }

// // ✅ Création du pipe et du processus enfant
// setup_pipe(pipe_fd);
// pid = fork();
// if (pid == -1)
// {
// 	perror("Erreur lors du fork");
// 	exit(1);
// }
// if (pid == 0)
// {
// 	// Processus enfant
// 	handle_child_process_pipeline(cmd, data, *pipe_in, pipe_fd);
// }
// else
// {
// 	// Processus parent
// 	handle_parent_process_pipeline(pid, cmd, pipe_in, pipe_fd);
// }
// }


void	executer_pipeline_cmd(t_cmd *cmd_lst, t_data *data)
{
	int		pipe_fd[2];
	int		pipe_in;
	char	*last_heredoc_files[256];
	t_cmd	*current_cmd;
	int		cmd_index;

	// printf("1 Je suis au debut de executer_pipeline_cmd\n");
	handle_heredocs_pipeline(cmd_lst);
	// printf("2 Je suis sortie de handle_heredocs_pipeline\n");
	create_heredoc_list(cmd_lst, last_heredoc_files);
	// printf("3 Je suis sortie de create_heredoc_list\n");
	pipe_in = 0;
	current_cmd = cmd_lst;
	cmd_index = 0;
	char *path_env = get_env_value(data->varenv_lst, "PATH");
	if (!path_env)
	{
		printf("🚨 ERREUR executer_pipeline_cmd: La variable PATH est NULL dans executer_pipeline_cmd() !!\n");
	}
	while (current_cmd)
	{
		// printf("4 Je passe par la boucle current_cmd dans executer_pipeline_cmd\n");
		handle_heredoc_input(last_heredoc_files[cmd_index]);
		// printf("5 Je suis sortie de handle_heredoc_input\n");
		execute_pipeline_command(current_cmd, data, &pipe_in, pipe_fd);
		// printf("6 Je suis sortie de execute_pipeline_command\n");
		current_cmd = current_cmd->next;
		cmd_index++;
	}
	// printf("7 Je suis sortie de la boucle\n");
	cleanup_pipeline(cmd_lst);
}
