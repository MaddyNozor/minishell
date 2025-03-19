/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:04:30 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/18 18:52:17 by sabellil         ###   ########.fr       */
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
		exit_with_error(data, cmd->value, "No such file or directory", 127);
	}
	env_array = convert_env_list_to_array(data->varenv_lst);
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
	exit_with_error(data, cmd->value, "Command execution failed", 127);
}

void	handle_child_process_pipeline(t_cmd *cmd, t_data *data, int pipe_in,
		int pipe_fd[2])
{
	char	*cmd_path;

	handle_pipe_redirections(cmd, pipe_in, pipe_fd);
	apply_redirections(cmd->redirection, data);
	if (is_builtin(cmd->value))
	{
		execute_builtin(cmd, data);
		exit(data->lst_exit);
	}
	cmd_path = find_cmd_path(cmd->value, data->varenv_lst, data);
	if (!cmd_path || access(cmd_path, X_OK) == -1)
	{
		printf("bash: %s: command not found\n", cmd->value);
		data->lst_exit = 127;
		update_exit_status(data->varenv_lst, data->lst_exit);
		exit(127);
	}
	execve(cmd_path, cmd->argv, convert_env_list_to_array(data->varenv_lst));
	perror("execve failed");
	data->lst_exit = 127;
	update_exit_status(data->varenv_lst, data->lst_exit);
	exit(127);
}

static void	handle_parent_process_pipeline_close_pipe(int *pipe_in,
		int pipe_fd[2])
{
	if (*pipe_in != 0)
		close(*pipe_in);
	*pipe_in = pipe_fd[0];
	close(pipe_fd[1]);
}
static bool	check_input_existence(t_redirection *redirection, t_data *data)
{
	int				input_fd;
	t_redirection	*redir;

	redir = redirection;
	while (redir)
	{
		if (redir->type == REDIRECT_IN)
		{
			input_fd = open(redir->file_name, O_RDONLY);
			if (input_fd == -1)
			{
				printf("bash: %s: No such file or directory\n",
						redir->file_name);
				data->lst_exit = 1;
				update_exit_status(data->varenv_lst, data->lst_exit);
				return (false);
			}
			close(input_fd);
		}
		redir = redir->next;
	}
	return (true);
}

static void	create_output_files(t_redirection *redirection)
{
	int				fd;
	t_redirection	*out;

	out = redirection;
	while (out)
	{
		if (out->type == REDIRECT_OUT || out->type == APPEND_OUT)
		{
			fd = open(out->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd != -1)
				close(fd);
		}
		out = out->next;
	}
}

static bool	handle_missing_input(t_cmd *cmd, t_data *data)
{
	int	devnull_fd;

	if (!check_input_existence(cmd->redirection, data))
	{
		devnull_fd = open("/dev/null", O_RDONLY);
		if (devnull_fd != -1)
			dup2(devnull_fd, STDIN_FILENO);
		return (false);
	}
	return (true);
}
static pid_t	create_forked_process(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_with_error(data, "fork", "Resource temporarily unavailable", 1);
	return (pid);
}


void	execute_pipeline_command(t_cmd *cmd, t_data *data, int *pipe_in,
		int pipe_fd[2])
{
	pid_t	pid;
	int		status;

	printf("Je passe par le execute pipeline command\n");
	if (!handle_missing_input(cmd, data))
		return ;
	create_output_files(cmd->redirection);
	setup_pipe(pipe_fd);
	pid = create_forked_process(data);
	if (pid == 0)
		handle_child_process_pipeline(cmd, data, *pipe_in, pipe_fd);
	else
	{
		if (!cmd->next)
		{
			waitpid(pid, &status, 0);
			while (wait(NULL) > 0)
				;
			if (WIFEXITED(status))
				data->lst_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->lst_exit = 128 + WTERMSIG(status);
			update_exit_status(data->varenv_lst, data->lst_exit);
		}
		handle_parent_process_pipeline_close_pipe(pipe_in, pipe_fd);
	}
}

void	executer_pipeline_cmd(t_cmd *cmd_lst, t_data *data)
	//TODO : Enlever une variable dans le corps de la fonction
{
	int pipe_fd[2];
	int pipe_in;
	t_cmd *current_cmd;
	int cmd_index;
	char *last_heredoc_files[256];

	handle_heredocs_pipeline(cmd_lst);
	create_heredoc_list(cmd_lst, last_heredoc_files);
	pipe_in = 0;
	current_cmd = cmd_lst;
	cmd_index = 0;
	if (!get_env_value(data->varenv_lst, "PATH"))
		printf("🚨 ERREUR: La variable PATH est NULL dans executer_pipeline_cmd() !!\n");
			// TODO : À remplacer
	while (current_cmd)
	{
		handle_heredoc_input(last_heredoc_files[cmd_index]);
		execute_pipeline_command(current_cmd, data, &pipe_in, pipe_fd);
		current_cmd = current_cmd->next;
		cmd_index++;
	}
	if (cmd_lst->pid != 0)
		data->lst_exit = cmd_lst->pid;
	update_exit_status(data->varenv_lst, data->lst_exit);
	cleanup_pipeline(cmd_lst);
}