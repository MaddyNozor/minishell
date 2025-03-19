/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:46:25 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/19 10:58:27 by sabellil         ###   ########.fr       */
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
				exit_with_error(data, curr->file_name, strerror(errno), 1);
				return;
			}
			if (dup2(*last_out_fd, STDOUT_FILENO) == -1)
			{
				exit_with_error(data, "dup2", strerror(errno), 1);
				return;
			}
			close(*last_out_fd);
		}
		curr = curr->next;
	}
}

void	handle_input_redirection(t_redirection *redirection, t_data *data,
	t_redir_state *state)
{
	t_redirection	*current;
	int				input_fd;

	current = redirection;
	while (current)
	{
		if (current->type == REDIRECT_IN)
		{
			input_fd = open(current->file_name, O_RDONLY);
			if (input_fd == -1)
			{
				exit_with_error(data, current->file_name, "No such file or directory", 1);
				state->input_redir_found = false;
				return;
			}
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
			state->input_fd = input_fd;
			state->input_redir_found = true;
		}
		else if (current->type == HEREDOC)
		{
			state->last_heredoc = current;
			state->input_redir_found = true;
		}
		current = current->next;
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

// void	handle_input_redirection(t_redirection *redirection, int *input_fd,
// 	t_redirection **last_heredoc, bool *input_redir_found)// avant ajout lst_exit
// {
// t_redirection	*current;

// current = redirection;
// while (current)
// {
// 	if (current->type == REDIRECT_IN)
// 	{
// 		*input_fd = open(current->file_name, O_RDONLY);
// 		if (*input_fd == -1)
// 		{
// 			fprintf(stderr, "bash: %s: No such file or directory\n", current->file_name);
// 			close(STDIN_FILENO);
// 			*input_redir_found = false;
// 			return;
			
// 		}
// 		dup2(*input_fd, STDIN_FILENO);
// 		close(*input_fd);
// 		*input_redir_found = true;
// 	}
// 	else if (current->type == HEREDOC)
// 	{
// 		*last_heredoc = current;
// 		*input_redir_found = true;
// 	}
// 	current = current->next;
// }
// }

// void	handle_output_redirections(t_redirection *redir, int *last_out_fd)//TODO : A virer a la fin (ajout de lst_exit)
// {
// 	t_redirection	*curr;
// 	int				flags;

// 	curr = redir;
// 	while (curr)
// 	{
// 		if (curr->type == REDIRECT_OUT || curr->type == APPEND_OUT)
// 		{
// 			if (*last_out_fd != -1)
// 				close(*last_out_fd);
// 			flags = O_WRONLY | O_CREAT;
// 			if (curr->type == REDIRECT_OUT)
// 				*last_out_fd = open(curr->file_name, flags | O_TRUNC, 0644);
// 			else if (curr->type == APPEND_OUT)
// 				*last_out_fd = open(curr->file_name, flags | O_APPEND, 0644);
// 			if (*last_out_fd == -1)
// 			{
// 				perror("ERREUR : Impossible d'ouvrir le fichier de sortie");
// 				return ;
// 			}
// 			// printf("✅ Redirection STDOUT -> %s, FD = %d\n", curr->file_name, *last_out_fd);
// 			// 🔥 Redirection vers STDOUT
// 			if (dup2(*last_out_fd, STDOUT_FILENO) == -1)
// 				perror("ERREUR : dup2 vers STDOUT a échoué");
// 			close(*last_out_fd);
// 		}
// 		curr = curr->next;
// 	}
// }
