/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:00:05 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/20 16:38:36 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	init_existing_env(t_varenv **varenv_lst, char **envp, t_data *data)
{
	char	*equal;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			name = ft_substr(envp[i], 0, equal - envp[i]);
			value = ft_strdup(equal + 1);
			if (name && value)
				create_varenv(data, varenv_lst, (t_varenv_data){name, value, false});
			free(name);
			free(value);
		}
		i++;
	}
	if (!get_env_value(*varenv_lst, "PATH"))
		create_varenv(NULL, varenv_lst, (t_varenv_data){"PATH", "/usr/bin:/bin", false});
	create_varenv(NULL, varenv_lst, (t_varenv_data){"?", "0", false});
}

void	init_minimalist_env(t_varenv **varenv_lst)
{
	char			*pwd;
	t_varenv_data	var_data;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	var_data = (t_varenv_data){"PWD", pwd, false};
	create_varenv(NULL, varenv_lst, var_data);
	var_data = (t_varenv_data){"SHLVL", "1", false};
	create_varenv(NULL, varenv_lst, var_data);
	var_data = (t_varenv_data){"_", "/usr/bin/env", false};
	create_varenv(NULL, varenv_lst, var_data);
	free(pwd);
}

t_varenv	*init_varenv(char **envp, t_data *data)
{
	t_varenv	*varenv_lst;

	varenv_lst = NULL;
	if (!envp || !*envp)
		init_minimalist_env(&varenv_lst);
	else
		init_existing_env(&varenv_lst, envp, data);
	// t_varenv *tmp = varenv_lst;//Pour verifier les varenv existantes
	// 	printf("---- Environnement chargé ----\n");
	// 	while (tmp)
	// 	{
	// 		printf("%s=%s\n", tmp->name, tmp->value);
	// 		tmp = tmp->next;
	// 	}
	// 	printf("-----------------------------\n");
	return (varenv_lst);
}
