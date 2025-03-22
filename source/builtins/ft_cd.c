/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:21:32 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 11:09:51 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

bool	update_env_var(t_varenv *varenv, char *key, char *value)
{
	t_varenv	*current;

	current = varenv;
	while (current)
	{
		if (ft_strcmp(current->name, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (true);
		}
		current = current->next;
	}
	return (false);
}

void	ft_update_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_env_var(data->varenv_lst, "PWD", cwd);
		free(cwd);
		data->lst_exit = 0;
	}
	else
	{
		printf("bash: getcwd: %s\n", strerror(errno));
		data->lst_exit = 1;
	}
	update_exit_status(data, data->lst_exit);
}

static int	handle_cd_error(t_data *data, char *path)
{
	printf("bash: cd: %s: %s\n", path, strerror(errno));
	data->lst_exit = 1;
	update_exit_status(data, data->lst_exit);
	return (1);
}

int	ft_cd(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	*home;

	path = NULL;
	if (cmd->argc == 1 || !cmd->argv[1])
	{
		home = get_env_value(data->varenv_lst, "HOME");
		if (!home)
		{
			printf("bash: cd: HOME not set\n");
			data->lst_exit = 1;
			update_exit_status(data, data->lst_exit);
			return (1);
		}
		path = home;
	}
	else
		path = cmd->argv[1];
	if (chdir(path) == -1)
		return (handle_cd_error(data, path));
	ft_update_pwd(data);
	data->lst_exit = 0;
	update_exit_status(data, data->lst_exit);
	return (0);
}
