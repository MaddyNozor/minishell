/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:19:05 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/19 17:38:03 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	handle_token_word(t_queue *queue, t_token **tok, t_cmd *current_cmd)
{
	t_token	*current_tok;
	t_data	*data;

	data = current_cmd->data; // Récupération de `data` depuis `current_cmd`
	current_tok = *tok;
	if (!current_cmd->value) // Si c'est le premier token WORD dans cette commande
	{
		current_cmd->value = ft_strdup(current_tok->content);
		if (!current_cmd->value)
		{
			printf("bash: allocation error\n");
			data->lst_exit = 1;
			return ;
		}
		enqueue_token(queue, current_tok->content, data);
		current_cmd->argc++;
	}
	else
	{
		enqueue_token(queue, current_tok->content, data);
		current_cmd->argc++;
	}
	while (current_tok->next && current_tok->next->type == WORD)
	{
		current_tok = current_tok->next;
		enqueue_token(queue, current_tok->content, data);
		current_cmd->argc++;
	}
	*tok = current_tok; // Mise à jour du pointeur pour `handle_tokens`
}
