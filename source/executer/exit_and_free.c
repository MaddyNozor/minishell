/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:10:56 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 11:50:03 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_queue(t_queue *queue)
{
	t_node	*tmp;
	t_node	*to_free;

	if (!queue)
		return ;
	tmp = queue->head;
	while (tmp)
	{
		to_free = tmp;
		tmp = tmp->next;
		free(to_free->content);
		free(to_free);
	}
	free(queue);
}

void	ft_free_all(t_data *data)
{
	rl_clear_history();
	if (!data)
		return ;
	if (data->varenv_lst)
		free_varenv(data->varenv_lst);
	if (data->cmd_lst)
		free_cmd_list(data->cmd_lst);
	if (data->tok_lst)
		free_token_list(&data->tok_lst);
}
