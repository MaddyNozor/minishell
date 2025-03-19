/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:28:53 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/19 17:44:46 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	handle_token_pipe(t_cmd **current_cmd, t_queue *queue)
{	
	t_cmd	*new_cmd;
	t_data	*data;

	transfer_queue_to_argv(queue, *current_cmd);
	data = (*current_cmd)->data;
	new_cmd = init_cmd_structs(data);
	if (!new_cmd)
	{
		printf("bash: allocation error\n");
		data->lst_exit = 1;
		return ;
	}
	(*current_cmd)->next = new_cmd;
	*current_cmd = new_cmd;
}


// void	handle_token_pipe(t_cmd **current_cmd, t_queue *queue)//TODO : A virer a la fin (ajout de lst exit)
// {	
// 	t_cmd *new_cmd;
// 	t_data *data;

// 	transfer_queue_to_argv(queue, *current_cmd);
// 	data = (*current_cmd)->data; // Récupérer data depuis current_cmd
// 	new_cmd = init_cmd_structs(data);
// 	if (!new_cmd)
// 		return ;
// 	(*current_cmd)->next = new_cmd;
// 	*current_cmd = new_cmd;
// }
