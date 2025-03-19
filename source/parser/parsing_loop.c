/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:24:19 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/19 17:31:07 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

t_cmd	*init_cmd_structs(t_data *data)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		printf("bash: allocation error\n");
		data->lst_exit = 1;
		return (NULL);
	}
	cmd->value = NULL;
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->pid = 0;
	cmd->redirection = NULL;
	cmd->next = NULL;
	cmd->data = data; // Stocker data dans la structure
	return (cmd);
}


void	handle_var_env_token(t_token **tok, t_queue *queue, t_cmd *current_cmd, t_varenv *varenv_lst)
{
	handle_var_env(*tok, queue, current_cmd, varenv_lst);
	if ((*tok)->next && (*tok)->next->type == WORD)
	{
		*tok = (*tok)->next;
		handle_token_word(queue, tok, current_cmd);
	}
}

void	handle_token_type(t_token **tok, t_cmd **current_cmd, t_queue *queue, t_varenv *varenv_lst)
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


void	process_tokens(t_token **tok, t_cmd **current_cmd, t_queue *queue, t_varenv *varenv_lst)
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

void	handle_tokens(t_token *tok, t_cmd **cmd_list, t_varenv *varenv_lst, t_data *data)
{
	t_queue	*queue;
	t_cmd	*current_cmd;

	queue = init_queue(data);
	current_cmd = init_cmd_structs(data);
	if (!current_cmd)
		return ;
	*cmd_list = current_cmd;
	process_tokens(&tok, &current_cmd, queue, varenv_lst);
	transfer_queue_to_argv(queue, current_cmd);
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


// void	handle_tokens(t_token *tok, t_cmd **cmd_list, t_varenv *varenv_lst)//TODO : A virer a la fin, refactorise
// {
// 	t_queue	*queue;
// 	t_cmd	*current_cmd;

// 	queue = init_queue();
// 	current_cmd = init_cmd_structs();
// 	*cmd_list = current_cmd;
// 	while (tok)
// 	{
// 		if (!tok->content)
// 		{
// 			tok = tok->next;
// 			continue ;
// 		}
// 		if (tok->type == PIPE)
// 			handle_token_pipe(&current_cmd, queue);
// 		else if (tok->type == VAR_ENV)
// 		{
// 			handle_var_env(tok, queue, current_cmd, varenv_lst);
			
// 			if (tok->next && tok->next->type == WORD)
// 			{
// 				tok = tok->next;
// 				handle_token_word(queue, &tok, current_cmd);
// 			}
// 		}
// 		else if (tok->type == WORD)
// 			handle_token_word(queue, &tok, current_cmd);
// 		else if (tok->type == REDIRECT_IN || tok->type == REDIRECT_OUT
// 					|| tok->type == APPEND_OUT || tok->type == HEREDOC)
// 		{
// 			handle_redirections(tok, &current_cmd, varenv_lst);
// 			tok = tok->next;
// 		}
// 		tok = tok->next;
// 	}
// 	transfer_queue_to_argv(queue, current_cmd);
// }