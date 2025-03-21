/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:46:25 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/21 15:11:10 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

static int	open_output_file(t_redirection *curr)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (curr->type == REDIRECT_OUT)
		return (open(curr->file_name, flags | O_TRUNC, 0644));
	return (open(curr->file_name, flags | O_APPEND, 0644));
}

void	handle_output_redirections(t_redirection *redir, t_data *data, int *last_out_fd)
{
	t_redirection	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == REDIRECT_OUT || curr->type == APPEND_OUT)
		{
			if (*last_out_fd != -1)
				close(*last_out_fd);
			*last_out_fd = open_output_file(curr);
			if (*last_out_fd == -1)
			{
				perror("ERREUR : Impossible d'ouvrir le fichier de sortie");
				// update_exit_status(data->varenv_lst, 1);
				update_exit_status(data, 1);
				return;
			}
			if (dup2(*last_out_fd, STDOUT_FILENO) == -1)
			{
				perror("ERREUR : dup2 vers STDOUT a échoué");
				// update_exit_status(data->varenv_lst, 1);
				update_exit_status(data, 1);
			}
			close(*last_out_fd);
		}
		curr = curr->next;
	}
}

void	handle_input_redirection(t_redirection *redirection, int *in_fd, t_redirection **lst_hered, bool *in_redir)
{
	t_redirection	*current;

	printf("📌 Je rentre dans handle_input_redirection\n");
	current = redirection;
	while (current)
	{
		if (current->type == REDIRECT_IN)
		{
			*in_fd = open(current->file_name, O_RDONLY);
			if (*in_fd == -1)
			{
				close(STDIN_FILENO);
				*in_redir = false;
				return ;
			}
			dup2(*in_fd, STDIN_FILENO);
			close(*in_fd);
			*in_redir = true;
		}
		else if (current->type == HEREDOC)
		{
			*lst_hered = current;
			*in_redir = true;
		}
		current = current->next;
	}
}

void	handle_pipe_redirections(t_cmd *cmd, int pipe_in, int pipe_fd[2])
{
	if (pipe_in != -1 && pipe_in != STDIN_FILENO)
	{
		if (dup2(pipe_in, STDIN_FILENO) == -1)
			perror("Erreur dup2 STDIN");
	}

	if (cmd->next && pipe_fd[1] != -1 && pipe_fd[1] != STDOUT_FILENO)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror("Erreur dup2 STDOUT");
		close(pipe_fd[1]);
	}
}

// void	handle_pipe_redirections(t_cmd *cmd, int pipe_in, int pipe_fd[2])//A garder par securite, retire pour leaks ls | echo Sara
// {
// 	if (pipe_in != 0)
// 	{
// 		if (dup2(pipe_in, STDIN_FILENO) == -1)
// 			perror("Erreur dup2 STDIN");
// 		close(pipe_in);
// 	}
// 	if (cmd->next)
// 	{
// 		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
// 			perror("Erreur dup2 STDOUT");
// 		close(pipe_fd[1]);
// 	}
// 	close(pipe_fd[0]);
// }