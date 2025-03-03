/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:42:31 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/03 12:45:44 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

t_queue	*init_queue(void)
{
	t_queue	*queue;

	queue = malloc(sizeof(t_queue));
	if (!queue)
		return (NULL);
	queue->head = NULL;
	queue->tail = NULL;
	return (queue);
}
// enqueue: qui ajoute un token dans la queue
void	enqueue_token(t_queue *queue, char *content)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	if (!queue->head)
		queue->head = new_node;
	else
		queue->tail->next = new_node;
	queue->tail = new_node;
	printf("MIS EN QUEUE Enqueued token: %s\n", content);
}

// dqueue : transferer la queue vers argv
void	transfer_queue_to_argv(t_queue *queue, t_cmd *cmd)
{
	int		count;
	t_node	*tmp;
	t_node	*to_free;

	count = 0;
	tmp = queue->head;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	cmd->argv = malloc(sizeof(char *) * (count + 1));
	if (!cmd->argv)
		return ;
	tmp = queue->head;
	count = 0;
	while (tmp)
	{
		cmd->argv[count] = tmp->content; // copier le contenu
		to_free = tmp;
		tmp = tmp->next;
		free(to_free); // liberer nœud
		count++;
	}
	cmd->argv[count] = NULL;
	queue->head = NULL; // reinit de la queue
	queue->tail = NULL;
}
