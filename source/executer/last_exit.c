/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:21:29 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/18 15:22:01 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void update_exit_status(t_varenv *varenv, int exit_status)
{
	t_varenv *current;

	current = varenv;
	while (current)
	{
		if (ft_strcmp(current->name, "?") == 0)
		{
			free(current->value);
			current->value = ft_itoa(exit_status);
			return;
		}
		current = current->next;
	}
	create_varenv(&varenv, "?", ft_itoa(exit_status), false);
}

char	*get_exit_status(t_varenv *varenv)
{
	while (varenv)
	{
		if (ft_strcmp(varenv->name, "?") == 0)
			return (ft_strdup(varenv->value));
		varenv = varenv->next;
	}
	return (NULL);
}
void	exit_with_error(t_data *data, char *message, int exit_code)
{
	printf("%s\n", message);
	data->lst_exit = exit_code;
	update_exit_status(data->varenv_lst, data->lst_exit);
	exit(exit_code);
}