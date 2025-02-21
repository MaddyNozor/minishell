/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:04:30 by sabellil          #+#    #+#             */
/*   Updated: 2025/02/21 18:44:51 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	execute_external_cmd(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;
	char	**env_array;

	cmd_path = find_cmd_path(cmd->value, data->varenv_lst);
	if (!cmd_path || access(cmd_path, X_OK) == -1)
	{
		perror("command not found");
		free(cmd_path);
		exit(127);
	}
	env_array = convert_env_list_to_array(data->varenv_lst);
	if (!env_array)
	{
		perror("env conversion failed");
		free(cmd_path);
		exit(127);
	}
	execve(cmd_path, cmd->argv, env_array);
	perror("execve failed");
	free(cmd_path);
	free_tab(env_array);
	exit(127);
}

void	handle_child_process_pipeline(t_cmd *cmd, t_data *data, int pipe_in,
		int pipe_fd[2])
{
	int	heredoc_fd;

	heredoc_fd = -1;
	setup_heredoc_fd(cmd, &heredoc_fd);
	setup_io_redirections(heredoc_fd, pipe_in, pipe_fd, cmd);
	apply_redirections(cmd->redirection);
	if (is_builtin(cmd->value))
	{
		execute_builtin(cmd, data);
		exit(0);
	}
	execute_external_cmd(cmd, data);
	perror("execve failed");
	exit(1);
}

void	handle_parent_process_pipeline(pid_t pid, t_cmd *data, int *pipe_in,
		int pipe_fd[2])//unlink a la fin?
{
	int	status;

	(void)data;
	fprintf(stderr, "Je vais attendre le processus enfant\n");
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	close(pipe_fd[1]);
	fprintf(stderr, "Je viens de close le pipe_fd1\n");
	*pipe_in = pipe_fd[0];
}

void	execute_pipeline_command(t_cmd *cmd, t_data *data, int *pipe_in,
		int pipe_fd[2])
{
	pid_t	pid;

	setup_pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
	{
		perror("Erreur lors du fork");
		exit(1);
	}
	if (pid == 0)
	{
		handle_child_process_pipeline(cmd, data, *pipe_in, pipe_fd);
	}
	else
		handle_parent_process_pipeline(pid, cmd, pipe_in, pipe_fd);
}

void	executer_pipeline_cmd(t_cmd *cmd_lst, t_data *data)
{
	int		pipe_fd[2];
	int		pipe_in;
	char	*last_heredoc_files[256];
	t_cmd	*current_cmd;
	int		cmd_index;

	handle_heredocs_pipeline(cmd_lst);
	create_heredoc_list(cmd_lst, last_heredoc_files);
	pipe_in = 0;
	current_cmd = cmd_lst;
	cmd_index = 0;
	while (current_cmd)
	{
		handle_heredoc_input(last_heredoc_files[cmd_index]);
		execute_pipeline_command(current_cmd, data, &pipe_in, pipe_fd);
		current_cmd = current_cmd->next;
		cmd_index++;
	}
	cleanup_pipeline(cmd_lst);
}
