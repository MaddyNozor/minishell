/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:10:03 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/21 15:14:04 by mairivie         ###   ########.fr       */
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

static void	handle_input_error(t_redirection *redirection, bool *output_created)
{
	t_redirection	*out;
	int				fd;

	out = redirection;
	while (out)
	{
		if ((out->type == REDIRECT_OUT || out->type == APPEND_OUT)
			&& !(*output_created))
		{
			fd = open(out->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd != -1)
				close(fd);
			*output_created = true;
		}
		out = out->next;
	}
}

static void	process_redirections(t_redirection *redirection,
									t_redir_state *state,
									t_data *data)
{
	t_redirection	*current;

	current = redirection;
	while (current)
	{
		if (current->type == REDIRECT_IN)
		{
			state->last_heredoc = NULL;
			state->input_fd = open(current->file_name, O_RDONLY);
			if (state->input_fd == -1)
			{
				handle_input_error(redirection, &state->output_created);
				printf("bash: %s: No such file or directory\n", current->file_name);
				// update_exit_status(data->varenv_lst, 1);
				update_exit_status(data, 1);
				state->input_fd = -1;
				state->output_created = false;
				return ;
			}
			close(state->input_fd);
		}
		else if (current->type == HEREDOC)
			state->last_heredoc = current;
		current = current->next;
	}
}

void	apply_redirections(t_redirection *redirection, t_data *data)
{
	t_redir_state	state;
	int				heredoc_fd;
	t_redirection	*fake;

	state.last_output_fd = -1;
	state.input_fd = -1;
	state.last_heredoc = NULL;
	state.input_redir_found = true;
	state.output_created = false;
	process_redirections(redirection, &state, data);
	handle_input_redirection(redirection, &state.input_fd, &fake, 
		&state.input_redir_found);
	heredoc_fd = -1;
	if (state.last_heredoc)
		heredoc_fd = open(state.last_heredoc->file_name, O_RDONLY);
	handle_heredoc_and_input(data, heredoc_fd, state.input_fd);
	if (state.last_heredoc)
		handle_heredoc_redirection(data, state.last_heredoc, &state.input_fd);
	if (!state.input_redir_found)
		return ;
	handle_output_redirections(redirection, data, &state.last_output_fd);
}
