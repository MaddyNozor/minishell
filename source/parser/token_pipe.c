/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:28:53 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/03 12:45:57 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

// debut token_pipe
void	handle_token_pipe(t_cmd **current_cmd, t_queue *queue)
{
	printf("Handling PIPE token...\n");
	transfer_queue_to_argv(queue, *current_cmd);
	t_cmd *new_cmd;
	new_cmd = init_cmd_structs(); // a chainer la precedente manuellement?
	if (!new_cmd)
		return ;
	(*current_cmd)->next = new_cmd;
	*current_cmd = new_cmd;
	printf("Created new command structure after PIPE.\n");
}