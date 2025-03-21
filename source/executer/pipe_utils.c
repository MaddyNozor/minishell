/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:04:28 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/21 13:31:54 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	setup_pipe(t_data *data, int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{      
		exit_with_error(data, "pipe", strerror(errno), 1);
		return;
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
