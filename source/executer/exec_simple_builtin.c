/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:44:00 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/03 12:15:26 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	execute_builtin(t_cmd *cmd, t_data *data)
{
	(void)data;
	if (ft_strncmp(cmd->value, "echo", 5) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd->value, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->value, "env", 4) == 0)
		ft_env(data, cmd);
	else if (ft_strncmp(cmd->value, "cd", 3) == 0)
		ft_cd(cmd, data->varenv_lst);
	else
		printf("Oops je l'ai pas encore code celui la!\n");
	// else if (ft_strncmp(cmd->value, "export", 7) == 0)
	// 	ft_export(cmd, data);
	// else if (ft_strncmp(cmd->value, "unset", 6) == 0)
	// 	ft_unset(cmd, data);

	// else if (ft_strncmp(cmd->value, "exit", 5) == 0)
	// 	ft_exit(cmd);
}

void	exec_simple_builtin_dir(t_cmd *cmd, t_data *data)
{
	int	saved_stdout;
	int	saved_stdin;

	(void)data;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	apply_redirections(cmd->redirection);
	execute_builtin(cmd, data);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	exec_simple_builtin_heredoc(t_cmd *cmd, t_data *data)
{
	handle_heredocs_simple_cmd(cmd->redirection);
	apply_redirections(cmd->redirection);
	execute_builtin(cmd, data);
	close_redirections(cmd->redirection);
	unlink_heredoc_temp(cmd->redirection);
}

void	exec_simple_builtin(t_cmd *cmd, t_data *data)
{
	if (cmd->redirection)
	{
		if (contains_heredoc(cmd->redirection))
		{
			fprintf(stderr, "🛠️ Cas commande simple en heredoc\n");
			fflush(stderr);
			exec_simple_builtin_heredoc(cmd, data);
		}
		else
		{
			fprintf(stderr, "🛠️ Cas commande simple avec autre redirection\n");
			fflush(stderr);
			exec_simple_builtin_dir(cmd, data);
		}
	}
	else
	{			
		fprintf(stderr, "🛠️ Cas commande simple builtin\n");
		fflush(stderr);
		execute_builtin(cmd, data);
	}
}
