/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:04:30 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 11:57:16 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	execute_external_cmd(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;
	char	**env_array;

	cmd_path = find_cmd_path(cmd->value, data->varenv_lst, data);
	if (!cmd_path || access(cmd_path, X_OK) == -1)
	{
		free(cmd_path);
		exit_with_error(data, cmd->value, "command not found", 127);
	}
	env_array = convert_env_list_to_array(data, data->varenv_lst);
	if (!env_array)
	{
		perror("env conversion failed");
		free(cmd_path);
		exit_with_error(data, "environment",
			"Failed to convert environment variables", 127);
	}
	if (!cmd->argv || !cmd->argv[0])
		exit_with_error(data, cmd->value, "Invalid arguments", 127);
	execve(cmd_path, cmd->argv, env_array);
	perror("execve failed");
	free(cmd_path);
	free_tab(env_array);
	(ft_free_all(data), exit(127));
}

static void	handle_child_process_pipeline(t_cmd *cmd, t_data *data, int pipe_in,
		int pipe_fd[2])
{
	char	*cmd_path;

	handle_pipe_redirections(cmd, pipe_in, pipe_fd);
	apply_redirections(cmd->redirection, data);
	if (is_builtin(cmd->value))
	{
		execute_builtin(cmd, data);
		(ft_free_all(data), exit(data->lst_exit));
	}
	cmd_path = find_cmd_path(cmd->value, data->varenv_lst, data);
	if (!cmd_path)
	{
		printf("bash: %s: command not found\n", cmd->value);
		data->lst_exit = 127;
		update_exit_status(data, data->lst_exit);
		close_pipe_fds(pipe_fd);
		(ft_free_all(data), exit(127));
	}
	execve(cmd_path, cmd->argv, convert_env_list_to_array(data,
			data->varenv_lst));
	perror("execve failed");
	data->lst_exit = 127;
	update_exit_status(data, data->lst_exit);
	close_pipe_fds(pipe_fd);
	(ft_free_all(data), exit(127));
}

static void	handle_parent_process_pipeline_close_pipe(int *pipe_in,
														int pipe_fd[2])
{
	if (*pipe_in != -1)
		close(*pipe_in);
	*pipe_in = pipe_fd[0];
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

void	execute_pipeline_command(t_cmd *cmd, t_data *data, int *pipe_in,
		int pipe_fd[2])
{
	pid_t	pid;

	if (!handle_missing_input(cmd, data))
		return ;
	create_output_files(cmd->redirection, data);
	pid = create_forked_process(data, pipe_fd);
	if (pid == 0)
	{
		handle_child_process_pipeline(cmd, data, *pipe_in, pipe_fd);
	}
	else
	{
		cmd->pid = pid;
		wait_for_pipeline_process(pid, data, !cmd->next);
		handle_parent_process_pipeline_close_pipe(pipe_in, pipe_fd);
		if (!cmd->next && *pipe_in != -1)
		{
			close(*pipe_in);
			*pipe_in = -1;
		}
	}
}

void	executer_pipeline_cmd(t_cmd *cmd_lst, t_data *data)
{
	int		pipe_fd[2];
	int		pipe_in;
	t_cmd	*current_cmd;
	int		cmd_index;
	char	*last_heredoc_files[256];

	handle_heredocs_pipeline(data, cmd_lst);
	create_heredoc_list(cmd_lst, last_heredoc_files);
	pipe_in = -1;
	current_cmd = cmd_lst;
	cmd_index = 0;
	if (!get_env_value(data->varenv_lst, "PATH"))
		;
	while (current_cmd)
	{
		handle_heredoc_input(data, last_heredoc_files[cmd_index]);
		if (current_cmd->next)
			setup_pipe(data, pipe_fd);
		else
			reset_pipe_fd(pipe_fd);
		execute_pipeline_command(current_cmd, data, &pipe_in, pipe_fd);
		current_cmd = current_cmd->next;
		cmd_index++;
	}
	finalize_pipeline_execution(cmd_lst, data, pipe_in);
}
