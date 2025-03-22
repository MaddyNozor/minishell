/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:02:30 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 11:11:33 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	ft_unset_utils(t_varenv *current, t_data *data)
{
	t_varenv	*temp;

	temp = current;
	if (!current->prev && current->next)
	{
		current->next->prev = NULL;
		data->varenv_lst = current->next;
	}
	else if (!current->next && current->prev)
		current->prev->next = NULL;
	else if (current->prev && current->next)
	{
		current->next->prev = current->prev;
		current->prev->next = current->next;
	}
	else
		data->varenv_lst = NULL;
	free(temp->name);
	free(temp->value);
	free(temp);
}

static bool	ft_remove_var(t_data *data, char *var_name)
{
	t_varenv	*current;

	current = data->varenv_lst;
	while (current)
	{
		if (ft_strcmp(var_name, current->name) == 0)
		{
			ft_unset_utils(current, data);
			return (true);
		}
		current = current->next;
	}
	return (false);
}

int	ft_unset(t_data *data, t_cmd *cmd)
{
	int	i;
	int	removed;

	if (cmd->argc < 2)
		return (0);
	i = 1;
	removed = 0;
	while (i < cmd->argc)
	{
		if (ft_remove_var(data, cmd->argv[i]))
			removed = 1;
		i++;
	}
	if (removed)
		data->lst_exit = 0;
	else
		data->lst_exit = 1;
	update_exit_status(data, data->lst_exit);
	return (data->lst_exit);
}
