/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:38:18 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/16 14:12:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	ft_env(t_data *data, t_cmd *cmd)
{
	t_varenv	*current;

	if (cmd->argv[1] != NULL)
	{
		fprintf(stderr, "bash: %s: command not found\n", cmd->argv[1]);
		_exit(127);
	}
	if (!data->varenv_lst)
	{
		fprintf(stderr, "bash: env: environment not available\n");
		_exit(1);
	}
	current = data->varenv_lst;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

//TODO = quid en cqs de vqleur sqns = comme ceux qu'on peut creer avec export ?
//TODO es-ce qu'il faut pas ajouter env: devant chaque variable ?
