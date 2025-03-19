/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:24:19 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/18 19:20:03 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

t_cmd	*init_cmd_structs(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->value = NULL;
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->pid = 0;
	cmd->redirection = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	handle_tokens(t_token *tok, t_cmd **cmd_list, t_varenv *varenv_lst)
{
	t_queue	*queue;
	t_cmd	*current_cmd;

	queue = init_queue();
	current_cmd = init_cmd_structs();
	*cmd_list = current_cmd;
	while (tok)
	{
		if (!tok->content)
		{
			tok = tok->next;
			continue ;
		}
		if (tok->type == PIPE)
			handle_token_pipe(&current_cmd, queue);
		else if (tok->type == VAR_ENV)
		{
			handle_var_env(tok, queue, current_cmd, varenv_lst);
			
			if (tok->next && tok->next->type == WORD)
			{
				tok = tok->next;
				handle_token_word(queue, &tok, current_cmd);
			}
		}
		else if (tok->type == WORD)
			handle_token_word(queue, &tok, current_cmd);
		else if (tok->type == REDIRECT_IN || tok->type == REDIRECT_OUT
					|| tok->type == APPEND_OUT || tok->type == HEREDOC)
		{
			handle_redirections(tok, &current_cmd, varenv_lst);
			tok = tok->next;
		}
		tok = tok->next;
	}
	transfer_queue_to_argv(queue, current_cmd);
}

t_cmd	*parser(t_token *tok, t_varenv *varenv_lst)
{
	t_cmd	*cmd_list;

	cmd_list = NULL;
	if (!tok)
	{
		printf("No tokens to parse.\n");
		return (NULL);
	}
	handle_tokens(tok, &cmd_list, varenv_lst);
	return (cmd_list);
}
