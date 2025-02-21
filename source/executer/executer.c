/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:38:39 by sabellil          #+#    #+#             */
/*   Updated: 2025/02/21 13:26:14 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

bool	is_builtin(const char *cmd_value)
{
	int			i;
	const char	*builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
	};

	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(cmd_value, builtins[i], ft_strlen(builtins[i]) + 1) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	executer_simple_cmd(t_cmd *cmd, t_data *data)
{
	if (cmd == NULL || cmd->value == NULL)
		return ;
	if (is_builtin(cmd->value))
		exec_simple_builtin(cmd, data);
	else
		exec_simple_extern_cmd(cmd, data);
}

void	executer(t_data *data)
{
	if (data->cmd_lst->next == NULL)
		executer_simple_cmd(data->cmd_lst, data);
	else
		executer_pipeline_cmd(data->cmd_lst, data);
}
