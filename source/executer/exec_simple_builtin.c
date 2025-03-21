/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:44:00 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/21 20:11:08 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	execute_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strncmp(cmd->value, "echo", 5) == 0)
		data->lst_exit = ft_echo(cmd, data);
	else if (ft_strncmp(cmd->value, "pwd", 4) == 0)
		data->lst_exit = ft_pwd(data);
	else if (ft_strncmp(cmd->value, "env", 4) == 0)
		data->lst_exit = ft_env(data, cmd);
	else if (ft_strncmp(cmd->value, "export", 7) == 0)
		data->lst_exit = ft_export(data, cmd);
	else if (ft_strncmp(cmd->value, "cd", 3) == 0)
		data->lst_exit = ft_cd(cmd, data);
	else if (ft_strncmp(cmd->value, "unset", 6) == 0)
		data->lst_exit = ft_unset(data, cmd);
	else if (ft_strncmp(cmd->value, "exit", 5) == 0)
	{
		ft_exit(cmd, data);
		return ;
	}
	else
	{
		data->lst_exit = 1;
	}
	update_exit_status(data, data->lst_exit);
}

void	exec_simple_builtin_dir(t_cmd *cmd, t_data *data)
{
	int	saved_stdout;
	int	saved_stdin;
	int	input_fd;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	apply_redirections(cmd->redirection, data);
	input_fd = open(cmd->redirection->file_name, O_RDONLY);
	if (input_fd == -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return ;
	}
	close(input_fd);
	execute_builtin(cmd, data);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	exec_simple_builtin_heredoc(t_cmd *cmd, t_data *data)
{
	handle_heredocs_simple_cmd(data, cmd->redirection);
	apply_redirections(cmd->redirection, data);
	execute_builtin(cmd, data);
	close_redirections(cmd->redirection);
	unlink_heredoc_temp(data, cmd->redirection);
}

void	exec_simple_builtin(t_cmd *cmd, t_data *data)
{
	if (cmd->redirection)
	{
		if (contains_heredoc(cmd->redirection))
			exec_simple_builtin_heredoc(cmd, data);
		else
			exec_simple_builtin_dir(cmd, data);
	}
	else
		execute_builtin(cmd, data);
}
