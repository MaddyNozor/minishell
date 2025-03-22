/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:04:28 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 11:54:57 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	setup_pipe(t_data *data, int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		exit_with_error(data, "pipe", strerror(errno), 1);
		return ;
	}
}

void	cleanup_pipeline(t_data *data, t_cmd *cmd_lst)
{
	t_cmd	*current_cmd;
	int		status;

	while (wait(&status) > 0)
		;
	current_cmd = cmd_lst;
	while (current_cmd)
	{
		unlink_heredoc_temp(data, current_cmd->redirection);
		current_cmd = current_cmd->next;
	}
}

void	reset_pipe_fd(int pipe_fd[2])
{
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
}

void	finalize_pipeline_execution(t_cmd *cmd_lst, t_data *data,
		int pipe_in)
{
	cleanup_pipeline(data, cmd_lst);
	if (pipe_in != -1)
		close(pipe_in);
}

void	close_pipe_fds(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
