/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:10:03 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/18 17:35:37 by sabellil         ###   ########.fr       */
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
			close(fd);
		}
		curr = curr->next;
	}
}

// static void	handle_input_files(t_redirection *redirection, int *input_fd,
// 		t_redirection **last_heredoc, bool *output_created)
// {
// 	t_redirection	*current;
// 	t_redirection	*out;
// 	int				fd;

// 	current = redirection;
// 	while (current)
// 	{
// 		if (current->type == REDIRECT_IN)
// 		{
// 			if (*last_heredoc)
// 				*last_heredoc = NULL;
// 			*input_fd = open(current->file_name, O_RDONLY);
// 			if (*input_fd == -1)
// 			{
// 				out = redirection;
// 				while (out)
// 				{
// 					if ((out->type == REDIRECT_OUT || out->type == APPEND_OUT)
// 						&& !(*output_created))
// 					{
// 						fd = open(out->file_name, O_WRONLY | O_CREAT | O_TRUNC,
// 								0644);
// 						if (fd != -1)
// 							close(fd);
// 						*output_created = true;
// 					}
// 					out = out->next;
// 				}
// 				fprintf(stderr, "bash: %s: No such file or directory\n",
// 						current->file_name);
// 				exit(1);
// 			}
// 			close(*input_fd);
// 		}
// 		else if (current->type == HEREDOC)
// 			*last_heredoc = current;
// 		current = current->next;
// 	}
// }




// void	apply_redirections(t_redirection *redirection, t_data *data)
// {
// 	int				last_output_fd;
// 	int				in_fd;
// 	t_redirection	*lst_heredoc;
// 	bool			is_in_redir;
// 	bool			output_created;

// 	last_output_fd = -1;
// 	in_fd = -1;
// 	lst_heredoc = NULL;
// 	is_in_redir = true;
// 	output_created = false;
// 	handle_input_files(redirection, &in_fd, &lst_heredoc, &output_created,
// 			data);
// 	handle_input_redirection(redirection, &in_fd, &lst_heredoc, &is_in_redir);
// 	if (lst_heredoc)
// 		handle_heredoc_and_input(open(lst_heredoc->file_name, O_RDONLY), in_fd);
// 	else
// 		handle_heredoc_and_input(-1, in_fd);
// 	if (lst_heredoc)
// 		handle_heredoc_redirection(lst_heredoc, &in_fd);
// 	if (!is_in_redir)
// 	{
// 		data->lst_exit = 1;
// 			// ✅ Mise à jour de `lst_exit` en cas d'échec de la redirection d'entrée
// 		update_exit_status(data->varenv_lst, data->lst_exit);
// 		return ;
// 	}
// 	handle_output_redirections(redirection, &last_output_fd);
// }
// Fonction gérant l'ouverture des fichiers de redirection
static bool	handle_input_file(t_redirection *current, int *input_fd, bool *output_created, t_redirection *redirection)
{
	*input_fd = open(current->file_name, O_RDONLY);
	if (*input_fd == -1)
	{
		// Si fichier d'entrée introuvable, on traite les fichiers de sortie
		t_redirection *out = redirection;
		while (out)
		{
			if ((out->type == REDIRECT_OUT || out->type == APPEND_OUT) && !(*output_created))
			{
				int fd = open(out->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd != -1)
					close(fd);
				*output_created = true;
			}
			out = out->next;
		}
		fprintf(stderr, "bash: %s: No such file or directory\n", current->file_name);
		return false;
	}
	close(*input_fd);
	return true;
}

// Fonction principale de gestion des fichiers d'entrée
static void	handle_input_files(t_redirection *redirection, int *input_fd, t_redirection **last_heredoc, bool *output_created)
{
	t_redirection	*current = redirection;
	while (current)
	{
		if (current->type == REDIRECT_IN)
		{
			if (*last_heredoc)
				*last_heredoc = NULL;
			if (!handle_input_file(current, input_fd, output_created, redirection)) 
				exit(1);
		}
		else if (current->type == HEREDOC)
			*last_heredoc = current;
		current = current->next;
	}
}

// Fonction principale de gestion des redirections
void	apply_redirections(t_redirection *redirection, t_data *data)
{
	int				last_output_fd = -1;
	int				input_fd = -1;
	t_redirection	*lst_heredoc = NULL;
	bool			is_in_redir = true;
	bool			output_created = false;

	handle_input_files(redirection, &input_fd, &lst_heredoc, &output_created);
	handle_input_redirection(redirection, &input_fd, &lst_heredoc, &is_in_redir);
	if (lst_heredoc)
		handle_heredoc_and_input(open(lst_heredoc->file_name, O_RDONLY), input_fd);
	else
		handle_heredoc_and_input(-1, input_fd);

	if (lst_heredoc)
		handle_heredoc_redirection(lst_heredoc, &input_fd);
	if (!is_in_redir)
	{
		data->lst_exit = 1;
		update_exit_status(data->varenv_lst, data->lst_exit);
		return ;
	}
	handle_output_redirections(redirection, &last_output_fd);
}
