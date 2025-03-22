/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:51:24 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 11:52:13 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

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
