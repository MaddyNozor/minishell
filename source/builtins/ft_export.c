/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:02:30 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 11:10:55 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

static bool	validate_and_extract(char *arg, char **name, char **value,
		int *error_flag)
{
	*name = NULL;
	*value = NULL;
	if (!arg || ft_strlen(arg) == 0)
		return (handle_invalid_identifier(arg, error_flag));
	if (!extract_name_value(arg, name, value) || !*name
		|| ft_strlen(*name) == 0)
	{
		free(*name);
		free(*value);
		return (handle_invalid_identifier(arg, error_flag));
	}
	if (!*value)
		*value = ft_strdup("");
	if (!is_valid_identifier(*name))
	{
		free(*name);
		free(*value);
		return (handle_invalid_identifier(arg, error_flag));
	}
	return (true);
}

static void	process_export_arg(t_data *data, char *arg, int *error_flag)
{
	char	*name;
	char	*value;

	if (!validate_and_extract(arg, &name, &value, error_flag))
		return ;
	if (!ft_strchr(arg, '='))
	{
		free(name);
		free(value);
		return ;
	}
	while (*value && isspace(*value))
		value++;
	if (!update_env_var(data->varenv_lst, name, value))
	{
		create_varenv(data, &data->varenv_lst,
			(t_varenv_data){name, value, false});
	}
	free(name);
	free(value);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	int	i;
	int	error_flag;

	if (cmd->argc == 1)
	{
		ft_print_list_export(data);
		return (0);
	}
	i = 1;
	error_flag = 0;
	while (i < cmd->argc)
		process_export_arg(data, cmd->argv[i++], &error_flag);
	data->lst_exit = error_flag;
	update_exit_status(data, data->lst_exit);
	return (error_flag);
}
