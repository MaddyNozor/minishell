/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:04:07 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/18 15:25:23 by sabellil         ###   ########.fr       */
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

char	*get_env_value(t_varenv *varenv_lst, const char *key)
{
	while (varenv_lst)
	{
		if (ft_strcmp(varenv_lst->name, key) == 0)
			return (varenv_lst->value);
		varenv_lst = varenv_lst->next;
	}
	return (NULL);
}

char	*check_direct_path(const char *cmd, t_varenv *varenv_lst)
{
	char	*path_env;

	path_env = get_env_value(varenv_lst, "PATH");
	if (!path_env || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (NULL);
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

char	*find_cmd_path(const char *cmd, t_varenv *varenv_lst)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*direct_path;

	path_env = get_env_value(varenv_lst, "PATH");
	if (!path_env)
	{
		// printf("🚨 ERREUR find_path_cmd: La variable PATH est NULL, impossible de chercher %s\n", cmd);
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			direct_path = ft_strdup(cmd);
			return (direct_path);
		}
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = find_cmd_in_paths(paths, cmd);
	if (!full_path)
	{
		free_tab(paths);
		return (NULL);
	}
	return (full_path);
}
