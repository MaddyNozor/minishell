/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:21:29 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/20 19:49:59 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	update_exit_status(t_varenv *varenv, int exit_status)
{
	t_varenv		*current;
	t_varenv_data	var_data;
	char			*exit_str;

	current = varenv;
	while (current)
	{
		if (ft_strcmp(current->name, "?") == 0)
		{
			free(current->value);
			current->value = ft_itoa(exit_status);
			return ;
		}
		current = current->next;
	}
	exit_str = ft_itoa(exit_status);
	var_data = (t_varenv_data){"?", exit_str, false};
	create_varenv(NULL, &varenv, var_data);
	free(exit_str);
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

void	exit_with_error(t_data *data, char *context, char *error_message, int exit_code)
{
	printf("bash: %s: %s\n", context, error_message);
	data->lst_exit = exit_code;
	update_exit_status(data->varenv_lst, data->lst_exit);
	(ft_free_all(data), exit(exit_code));
}
void	exit_with_error_readline(t_data *data, char *context, char *error_message, int exit_code)
{
	if (ft_strcmp(context, "readline") != 0)
		printf("bash: %s: %s\n", context, error_message);
	if (data)
	{
		data->lst_exit = exit_code;
		update_exit_status(data->varenv_lst, data->lst_exit);
	}
	exit(exit_code);
}