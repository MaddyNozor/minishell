/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:42:31 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/21 15:22:01 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

t_queue	*init_queue(t_data *data)
{
	t_queue	*queue;

	queue = malloc(sizeof(t_queue));
	if (!queue)
	{
		printf("bash: allocation error\n");
		data->lst_exit = 1;
		return (NULL);
	}
	queue->head = NULL;
	queue->tail = NULL;
	return (queue);
}

bool	enqueue_token(t_queue *queue, char *content, t_data *data)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
	{
		printf("bash: allocation error\n");
		data->lst_exit = 1;
		return (false);
	}
	new_node->content = ft_strdup(content);
	if (!new_node->content)
	{
		printf("bash: allocation error\n");
		data->lst_exit = 1;
		free(new_node);
		return (false);
	}
	new_node->next = NULL;
	if (!queue->head)
		queue->head = new_node;
	else
		queue->tail->next = new_node;
	queue->tail = new_node;
	return (true);
}

static void	copy_and_free_node(t_node **tmp, char **argv, int *count)
{
	t_node	*to_free;

	argv[*count] = (*tmp)->content;
	to_free = *tmp;
	*tmp = (*tmp)->next;
	free(to_free);
	(*count)++;
}

void	transfer_queue_to_argv(t_queue *queue, t_cmd *cmd)
{
	int		count;
	t_node	*tmp;

	count = 0;
	tmp = queue->head;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	cmd->argv = malloc(sizeof(char *) * (count + 1));
	if (!cmd->argv)
	{
		printf("bash: allocation error\n");
		cmd->data->lst_exit = 1;
		return ;
	}
	tmp = queue->head;
	count = 0;
	while (tmp)
		copy_and_free_node(&tmp, cmd->argv, &count);
	cmd->argv[count] = NULL;
	queue->head = NULL;
	queue->tail = NULL;
}
