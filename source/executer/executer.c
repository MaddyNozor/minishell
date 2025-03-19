/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:38:39 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/19 11:03:45 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

extern volatile sig_atomic_t g_sig_caught;

static void	sig_quit_handler()
{
	g_sig_caught = SIGQUIT;
	// rl_redisplay();
	ft_printf("\nIs it a bird ? Is it a plane ? No ! It's Super-SIGQUIT!\n");
	// rl_on_new_line();
	// rl_on_new_line();
	rl_redisplay();
}

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
    {
        if (cmd && cmd->redirection && contains_heredoc(cmd->redirection))
        {
            handle_heredocs_simple_cmd(data, cmd->redirection);
            unlink_heredoc_temp(cmd->redirection);
        }
        return;
    }
    if (is_builtin(cmd->value))
    {
        exec_simple_builtin(cmd, data);
        update_exit_status(data->varenv_lst, data->lst_exit);
    }
    else
        exec_simple_extern_cmd(cmd, data);
}


void	executer(t_data *data)
{
	signal(SIGQUIT, sig_quit_handler);
	if (data->cmd_lst->next == NULL)
		executer_simple_cmd(data->cmd_lst, data);
	else
	{
// 	t_cmd *current_cmd;

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
