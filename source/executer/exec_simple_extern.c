/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_extern.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:09:14 by sabellil          #+#    #+#             */
/*   Updated: 2025/02/21 13:24:39 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

void	handle_child_process(t_cmd *cmd, t_data *data)
{
	apply_redirections(cmd->redirection);
	execute_external_cmd(cmd, data);
}

void	handle_parent_process(pid_t pid, t_cmd *cmd)
{
	int	status;

	waitpid(pid, &status, 0);
	close_redirections(cmd->redirection);
	unlink_heredoc_temp(cmd->redirection);
}

void	exec_simple_extern_cmd(t_cmd *cmd, t_data *data)
{
	pid_t	pid;

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
