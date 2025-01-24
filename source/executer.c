/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:38:39 by sabellil          #+#    #+#             */
/*   Updated: 2025/01/24 14:33:31 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

// Placeholder pour la fonction exec_simple_builtin
void exec_simple_builtin(t_cmd *cmd, t_data *data)
{
    (void)cmd;
    (void)data;
    // TODO: Implémenter la gestion des commandes built-in
}

// Placeholder pour la fonction exec_simple_extern_cmd
void exec_simple_extern_cmd(t_cmd *cmd, t_data *data, char **envp)
{
    (void)cmd;
    (void)data;
    (void)envp;
    // TODO: Implémenter la gestion des commandes externes
}

// Placeholder pour la fonction executer_pipeline_cmd
void executer_pipeline_cmd(t_cmd *cmd_lst, char **envp)
{
    (void)cmd_lst;
    (void)envp;
    // TODO: Implémenter la gestion des pipelines
}

bool	is_builtin(const char *cmd_value)
{
	const char	*builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
	};
	int			i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(cmd_value, builtins[i], ft_strlen(builtins[i]) + 1) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	executer_simple_cmd(t_cmd *cmd, t_data *data, char **envp)
{
	if (cmd == NULL || cmd->value == NULL)
		return ;
	if (is_builtin(cmd->value))
		exec_simple_builtin(cmd, data); //TODO
	else
		exec_simple_extern_cmd(cmd, data, envp); //TODO
}

void	executer(t_data *data, char **envp)
{
	if (data->cmd_lst->next == NULL)
		executer_simple_cmd(data->cmd_lst, data, envp);
	else
		executer_pipeline_cmd(data->cmd_lst, envp);//TODO
}
