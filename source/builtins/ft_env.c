/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:38:18 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 11:10:08 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

static int	handle_env_error(t_data *data, char *arg, int exit_code)
{
	if (arg)
		printf("env: ‘%s’: No such file or directory\n", arg);
	else
		printf("bash: env: No such file or directory\n");
	data->lst_exit = exit_code;
	update_exit_status(data, data->lst_exit);
	return (exit_code);
}

int	ft_env(t_data *data, t_cmd *cmd)
{
	t_varenv	*current;

	if (!get_env_value(data->varenv_lst, "PATH"))
		return (handle_env_error(data, NULL, 127));
	if (cmd->argv[1] != NULL)
		return (handle_env_error(data, cmd->argv[1], 127));
	if (!data->varenv_lst)
		return (handle_env_error(data, NULL, 1));
	current = data->varenv_lst;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	data->lst_exit = 0;
	update_exit_status(data, data->lst_exit);
	return (0);
}
