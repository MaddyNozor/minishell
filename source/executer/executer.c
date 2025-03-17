/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:38:39 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/17 12:25:56 by sabellil         ###   ########.fr       */
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
	// printf("Je suis dans executer\n");
	if (data->cmd_lst->next == NULL)
		executer_simple_cmd(data->cmd_lst, data);
	else
	{
// 		t_cmd *current_cmd;

// 	// Vérifier toutes les commandes envoyées à l'exécution
// 	current_cmd = data->cmd_lst;
// 	while (current_cmd)
// 	{
// 		printf("➡️ Commande envoyée à l'exécution : %s\n", current_cmd->value);
// 		current_cmd = current_cmd->next;
// 	}
//  printf("J'entre dnas executer_pipeline_cmd\n");
				executer_pipeline_cmd(data->cmd_lst, data);

	}
}
