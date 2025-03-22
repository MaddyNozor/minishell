/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:24:19 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 12:02:28 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	handle_var_env_token(t_token **tok, t_queue *queue, t_cmd *current_cmd,
		t_varenv *varenv_lst)
{
	hvar(*tok, queue, current_cmd, varenv_lst);
	if ((*tok)->next && (*tok)->next->type == WORD)
	{
		*tok = (*tok)->next;
		handle_token_word(queue, tok, current_cmd);
	}
}

void	handle_token_type(t_token **tok, t_cmd **current_cmd, t_queue *queue,
		t_varenv *varenv_lst)
{
	if ((*tok)->type == PIPE)
		handle_token_pipe(current_cmd, queue);
	else if ((*tok)->type == VAR_ENV)
		handle_var_env_token(tok, queue, *current_cmd, varenv_lst);
	else if ((*tok)->type == WORD)
		handle_token_word(queue, tok, *current_cmd);
	else if ((*tok)->type == REDIRECT_IN || (*tok)->type == REDIRECT_OUT
		|| (*tok)->type == APPEND_OUT || (*tok)->type == HEREDOC)
	{
		handle_redirections(*tok, current_cmd, varenv_lst);
		*tok = (*tok)->next;
	}
}

void	process_tokens(t_token **tok, t_cmd **current_cmd, t_queue *queue,
		t_varenv *varenv_lst)
{
	while (*tok)
	{
		if (!(*tok)->content)
		{
			*tok = (*tok)->next;
			continue ;
		}
		handle_token_type(tok, current_cmd, queue, varenv_lst);
		*tok = (*tok)->next;
	}
}

void	handle_tokens(t_token *tok, t_cmd **cmd_list, t_varenv *varenv_lst,
		t_data *data)
{
	t_queue	*queue;
	t_cmd	*current_cmd;

	current_cmd = init_cmd_structs(data);
	if (!current_cmd)
		return ;
	queue = init_queue(data);
	*cmd_list = current_cmd;
	process_tokens(&tok, &current_cmd, queue, varenv_lst);
	transfer_queue_to_argv(queue, current_cmd);
	free_queue(queue);
}

t_cmd	*parser(t_token *tok, t_varenv *varenv_lst, t_data *data)
{
	t_cmd	*cmd_list;

	cmd_list = NULL;
	if (!tok)
	{
		printf("No tokens to parse.\n");
		return (NULL);
	}
	handle_tokens(tok, &cmd_list, varenv_lst, data);
	return (cmd_list);
}
