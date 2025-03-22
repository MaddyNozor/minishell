/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:04:07 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 11:52:31 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

static char	*join_path_cmd(const char *path, const char *cmd)
{
	char	*full_path;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

char	*find_cmd_in_paths(char **paths, const char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = join_path_cmd(paths[i], cmd);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
		{
			free_tab(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*handle_cmd_not_found(t_data *data)
{
	data->lst_exit = 127;
	update_exit_status(data, data->lst_exit);
	return (NULL);
}

static char	**get_paths_from_env(t_varenv *varenv_lst, t_data *data)
{
	char	*path_env;
	char	**paths;

	path_env = get_env_value(varenv_lst, "PATH");
	if (!path_env && data->secret_path)
		path_env = ft_strdup(data->secret_path);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	return (paths);
}

char	*find_cmd_path(const char *cmd, t_varenv *varenv_lst, t_data *data)
{
	char	**paths;
	char	*full_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (handle_cmd_not_found(data));
	}
	paths = get_paths_from_env(varenv_lst, data);
	if (!paths)
		return (handle_cmd_not_found(data));
	full_path = find_cmd_in_paths(paths, cmd);
	if (full_path)
		return (full_path);
	free_tab(paths);
	return (handle_cmd_not_found(data));
}
