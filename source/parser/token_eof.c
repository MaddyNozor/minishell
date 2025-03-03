/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_eof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:20:30 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/03 12:45:52 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	handle_EOF(t_queue *queue, t_cmd *current_cmd)
{
	printf("Handling EOF token. Transferring queue to argv.\n");
	transfer_queue_to_argv(queue, current_cmd);
}