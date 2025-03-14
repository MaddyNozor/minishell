/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecole <ecole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:04:30 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/13 18:35:52 by ecole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	execute_external_cmd(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;
	char	**env_array;

	// printf("On passe par la fonction execute_external_cmd\n");
	cmd_path = find_cmd_path(cmd->value, data->varenv_lst);
	if (!cmd_path || access(cmd_path, X_OK) == -1)
	{
		printf("bash: %s: command not found\n", cmd->value);
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
	// printf("🚀 Avant execve(), est-ce que %s existe ? %d\n",
    //    cmd->argv[1], access(cmd->argv[1], F_OK) == 0);
	// printf("🔍 Vérification après heredoc : commande reçue = %s\n", cmd->value);
	execve(cmd_path, cmd->argv, env_array);
	perror("execve failed");
	free(cmd_path);
	free_tab(env_array);
	exit(127);
}

void	handle_child_process_pipeline(t_cmd *cmd, t_data *data, int pipe_in, int pipe_fd[2])
{
	int		input_fd;
	char	*cmd_path;
	t_pipe_data pipe_data; // ✅ Création de la structure pour stocker les pipes et le heredoc_fd

	pipe_data.heredoc_fd = -1;
	setup_heredoc_fd(cmd, &pipe_data.heredoc_fd);
	pipe_data.pipe_in = pipe_in;
	pipe_data.pipe_fd[0] = pipe_fd[0];
	pipe_data.pipe_fd[1] = pipe_fd[1];

	setup_io_redirections(&pipe_data, cmd, data); // ✅ Utilisation de la structure

	cmd_path = find_cmd_path(cmd->value, data->varenv_lst);
	if (!cmd_path)
	{
		printf("bash: %s: command not found\n", cmd->value);
		if (cmd->next) // 🔴 Si ce n'est pas la dernière commande du pipeline
		{
			close(pipe_fd[1]); // Fermer la sortie pour éviter un blocage
			exit(127); // Quitte sans bloquer les autres commandes
		}
		exit(127); // Dernière commande, erreur normale
	}

	if (is_builtin(cmd->value)) // ✅ Vérification des builtins
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

// void	handle_child_process_pipeline(t_cmd *cmd, t_data *data, int pipe_in, int pipe_fd[2])
// {
// 	int	heredoc_fd;
// 	int	input_fd;
// 	char	*cmd_path;

// 	heredoc_fd = -1;
// 	setup_heredoc_fd(cmd, &heredoc_fd);
// 	// setup_io_redirections(heredoc_fd, pipe_in, pipe_fd, cmd);

// 	setup_io_redirections(heredoc_fd, pipe_in, pipe_fd, cmd, data);

// 	cmd_path = find_cmd_path(cmd->value, data->varenv_lst);
// 	if (!cmd_path)
// 	{
// 		printf("bash: %s: command not found\n", cmd->value);
// 		if (cmd->next) // 🔴 Si ce n'est pas la dernière commande du pipeline
// 		{
// 			close(pipe_fd[1]); // Fermer la sortie pour éviter un blocage
// 			exit(127); // Quitte sans bloquer les autres commandes
// 		}
// 		exit(127); // Dernière commande, erreur normale
// 	}
// 		if (is_builtin(cmd->value))// Ajout pour bien fermer si le fichier apres builtin < nexiste pas, potentiellement inutile 
// 	{
// 		input_fd = open(cmd->redirection->file_name, O_RDONLY);
// 		if (input_fd == -1)
// 		{
// 			printf("bash: %s: No such file or directory\n", cmd->redirection->file_name);
// 			exit(1);
// 		}
// 		execute_builtin(cmd, data);
// 		exit(0);
// 	}
// 	execute_external_cmd(cmd, data);
// 	perror("execve failed");
// 	exit(127);
// }

// void	handle_child_process_pipeline(t_cmd *cmd, t_data *data, int pipe_in,
// 		int pipe_fd[2])
// {
// 	int	heredoc_fd;
// 	int	input_fd;
// 	// char	*cmd_path;

// 	heredoc_fd = -1;
// 	setup_heredoc_fd(cmd, &heredoc_fd);
// 	setup_io_redirections(heredoc_fd, pipe_in, pipe_fd, cmd);
// 	apply_redirections(cmd->redirection);
// 	// cmd_path = find_cmd_path(cmd->value, data->varenv_lst);
// 	// if (!cmd_path || access(cmd_path, X_OK) == -1)
// 	// {
// 	// 	printf("bash: %s: command not found\n", cmd->value);
// 	// 	free(cmd_path);
// 	// 	exit(127);
// 	// }
// 	if (is_builtin(cmd->value))// Ajout pour bien fermer si le fichier apres builtin < nexiste pas, potentiellement inutile 
// 	{
// 		input_fd = open(cmd->redirection->file_name, O_RDONLY);
// 		if (input_fd == -1)
// 		{
// 			printf("bash: %s: No such file or directory\n", cmd->redirection->file_name);
// 			exit(1);
// 		}
// 		execute_builtin(cmd, data);
// 		exit(0);
// 	}
// 	execute_external_cmd(cmd, data);
// 	perror("execve failed");
// 	exit(1);
// }

void	handle_parent_process_pipeline(pid_t pid, t_cmd *data, int *pipe_in,
		int pipe_fd[2])
{
	int	status;

	(void)data;//TODO : a virer si pas besoin a la fin du projet
	// fprintf(stderr, "Je vais attendre le processus enfant\n");
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	close(pipe_fd[1]);
	// fprintf(stderr, "Je viens de close le pipe_fd1\n");
	*pipe_in = pipe_fd[0];
}

void	execute_pipeline_command(t_cmd *cmd, t_data *data, int *pipe_in,
		int pipe_fd[2])
{
	pid_t	pid;

	setup_pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
	{
		perror("Erreur lors du fork");
		exit(1);
	}
	if (pid == 0)
	{
		// printf("Avant d'entrer dans child process Je traite la commande %s\n", cmd->value);
		handle_child_process_pipeline(cmd, data, *pipe_in, pipe_fd);

	}
	else
		handle_parent_process_pipeline(pid, cmd, pipe_in, pipe_fd);
}

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
