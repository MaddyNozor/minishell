/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:38:18 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/18 12:30:40 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

int	ft_env(t_data *data, t_cmd *cmd)
{
	t_varenv	*current;

	if (cmd->argv[1] != NULL)
	{
		printf("bash: %s: command not found\n", cmd->argv[1]);
		return (127);
	}
	if (!data->varenv_lst)
	{
		printf("bash: env: environment not available\n");
		return (1);
	}
	current = data->varenv_lst;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}

//TODO = quid en cqs de vqleur sqns = comme ceux qu'on peut creer avec export ?
//TODO es-ce qu'il faut pas ajouter env: devant chaque variable ?
