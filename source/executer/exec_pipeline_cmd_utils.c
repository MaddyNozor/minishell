/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_cmd_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:39:12 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 11:48:22 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	wait_for_pipeline_process(pid_t pid, t_data *data, bool is_last)
{
	int	status;

	if (!is_last)
		return ;
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status))
		data->lst_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->lst_exit = 128 + WTERMSIG(status);
	update_exit_status(data, data->lst_exit);
}

pid_t	create_forked_process(t_data *data, int pipe_fd[2])
{
	pid_t	pid;

	signal(SIGINT, sig_int_handler_fork);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit_with_error(data, "fork", "Resource temporarily unavailable", 1);
	}
	return (pid);
}

bool	check_input_existence(t_redirection *redirection, t_data *data)
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
				update_exit_status(data, data->lst_exit);
				return (false);
			}
			close(input_fd);
		}
		redir = redir->next;
	}
	return (true);
}

void	create_output_files(t_redirection *redirection, t_data *data)
{
	int				fd;
	t_redirection	*out;

	out = redirection;
	while (out)
	{
		if (out->type == REDIRECT_OUT || out->type == APPEND_OUT)
		{
			fd = open(out->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				exit_with_error(data, out->file_name, strerror(errno), 1);
				return ;
			}
			close(fd);
		}
		out = out->next;
	}
}

bool	handle_missing_input(t_cmd *cmd, t_data *data)
{
	int	null_input_fd;

	if (!check_input_existence(cmd->redirection, data))
	{
		null_input_fd = open("/dev/null", O_RDONLY);
		if (null_input_fd != -1)
			dup2(null_input_fd, STDIN_FILENO);
		return (false);
	}
	return (true);
}
