/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_extern.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:09:14 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/08 19:43:30 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

// void	handle_child_process(t_cmd *cmd, t_data *data)
// {	
	
// 	printf("J'entre dans handle_child_process\n");
// 	apply_redirections(cmd->redirection);
// 	printf("Je suis de retour dans handle_child_process\n");
// 	execute_external_cmd(cmd, data);
// }
void	handle_child_process(t_cmd *cmd, t_data *data)
{
	int	input_fd;

	printf("je suis sortie de apply redirections\n");

	apply_redirections(cmd->redirection);

	// 🔥 Vérifier si une redirection d'entrée existe avant d'ouvrir un fichier
	if (cmd->redirection && cmd->redirection->type == REDIR_IN)
	{
		printf("🔍 Je tente d'ouvrir %s en lecture seule\n", cmd->redirection->file_name);
		input_fd = open(cmd->redirection->file_name, O_RDONLY);
		printf("j'ai essayé d'ouvrir\n");

		if (input_fd == -1)
		{
			fprintf(stderr, "bash: %s: No such file or directory\n", cmd->redirection->file_name);
			exit(1);  // ⏹️ On quitte immédiatement pour empêcher toute exécution
		}
		close(input_fd);
	}

	printf("Je vais bientôt exécuter la commande externe\n");
	execute_external_cmd(cmd, data);
}

void	handle_parent_process(pid_t pid, t_cmd *cmd)
{
	int	status;

	waitpid(pid, &status, 0);
	close_redirections(cmd->redirection);
	unlink_heredoc_temp(cmd->redirection);

	// 🔥 Vérifier si la commande exécutée est `clear`
	if (strcmp(cmd->value, "clear") == 0)
		printf("\033[H\033[J");  // 🔥 Efface l'écran
	write(1, "\n", 1);
}



void	exec_simple_extern_cmd(t_cmd *cmd, t_data *data)
{
	pid_t	pid;
	
	// printf("Je suis dans exec_simple_cmd\n");
	if (!cmd || !cmd->value || !cmd->argv)
		return ;
	if (contains_heredoc(cmd->redirection))
		handle_heredocs_simple_cmd(cmd->redirection);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		handle_child_process(cmd, data);
	else
		handle_parent_process(pid, cmd);
}
