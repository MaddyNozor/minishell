/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:19:05 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/21 15:24:15 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

static void	add_word_to_queue(t_queue *queue, char *content, t_cmd *current_cmd)
{
	t_data *data;

	data = current_cmd->data;
	enqueue_token(queue, content, data);
	current_cmd->argc++;
}

void	handle_token_word(t_queue *queue, t_token **tok, t_cmd *current_cmd)
{
	t_token	*current_tok;
	t_data	*data;

	data = current_cmd->data;
	current_tok = *tok;
	if (!current_cmd->value)
	{
		current_cmd->value = ft_strdup(current_tok->content);
		if (!current_cmd->value)
		{
			printf("bash: allocation error\n");
			data->lst_exit = 1;
			return ;
		}
		add_word_to_queue(queue, current_tok->content, current_cmd);
	}
	else
		add_word_to_queue(queue, current_tok->content, current_cmd);

	while (current_tok->next && current_tok->next->type == WORD)
	{
		current_tok = current_tok->next;
		add_word_to_queue(queue, current_tok->content, current_cmd);
	}
	*tok = current_tok;
}
