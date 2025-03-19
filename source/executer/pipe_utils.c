/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:04:28 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/19 11:32:47 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	setup_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("Erreur lors de la creation du pipe");
		exit(1);
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

// void	cleanup_pipeline(t_cmd *cmd_lst)//TODO : A virer a la fin 
// {
// 	t_cmd	*current_cmd;
// 	int		status;

// 	while (wait(&status) > 0)
// 		;
// 	current_cmd = cmd_lst;
// 	while (current_cmd)
// 	{
// 		unlink_heredoc_temp(data, cmd->redirection);
// 		current_cmd = current_cmd->next;
// 	}
// }
