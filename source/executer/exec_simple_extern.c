/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_extern.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:09:14 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/20 15:10:50 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	handle_child_process(t_cmd *cmd, t_data *data)
{
	int	input_fd;

	apply_redirections(cmd->redirection, data);
	if (cmd->redirection && cmd->redirection->type == REDIRECT_IN)
	{
		input_fd = open(cmd->redirection->file_name, O_RDONLY);
		if (input_fd == -1)
		{
			update_exit_status(data->varenv_lst, 1);
			exit(data->lst_exit);
		}
		close(input_fd);
	}
	execute_external_cmd(cmd, data);
}

void	handle_parent_process(pid_t pid, t_cmd *cmd, t_data *data)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->lst_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->lst_exit = 128 + WTERMSIG(status);
	update_exit_status(data->varenv_lst, data->lst_exit);
	close_redirections(cmd->redirection);
	unlink_heredoc_temp(data, cmd->redirection);
	if (strcmp(cmd->value, "clear") == 0)
		printf("\033[H\033[J");
}
void	exec_simple_extern_cmd(t_cmd *cmd, t_data *data)
{
	pid_t	pid;

	if (!cmd || !cmd->value || !cmd->argv)
		return ;
	if (contains_heredoc(cmd->redirection))
		handle_heredocs_simple_cmd(data, cmd->redirection);
	pid = fork();
	if (pid == -1)
	{
		// printf("bash: fork failed\n");
		// 	//TODO : Voir ailleurs quel code est utilise
		update_exit_status(data->varenv_lst, 1);
		exit(1);//return dans l'ancienne version
	}
	if (pid == 0)
		handle_child_process(cmd, data);
	else
		handle_parent_process(pid, cmd, data);
}
