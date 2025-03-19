/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:19:05 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/18 19:20:55 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	handle_token_word(t_queue *queue, t_token **tok, t_cmd *current_cmd)
{
	t_token	*current_tok;

	current_tok = *tok;
	// printf("Handling WORD token: %s\n", current_tok->content);
	if (!current_cmd->value)
	// Si c'est le premier token WORD dans cette commande
	{
		current_cmd->value = ft_strdup(current_tok->content);
		enqueue_token(queue, current_tok->content);
		current_cmd->argc++;
		// printf("Assigned command name: %s\n", current_cmd->value);
	}
	else
	{
		enqueue_token(queue, current_tok->content);
		current_cmd->argc++;
		// printf("Added argument: %s, new argc: %d\n", current_tok->content,
		// 		current_cmd->argc);
	}
	while (current_tok->next && current_tok->next->type == WORD)
	{
		current_tok = current_tok->next;
		enqueue_token(queue, current_tok->content);
		current_cmd->argc++;
		printf("Chained argument: %s, new argc: %d\n", current_tok->content,
				current_cmd->argc);
	}
	*tok = current_tok; // maj du pointeur pour handle_tokens
	// printf("🔍 handle_token_word : tok->content = %s, current_cmd->value = %s\n",
	// 	(*tok)->content, current_cmd->value);
}
