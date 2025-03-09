/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:00:05 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/09 16:37:18 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	init_existing_env(t_varenv **varenv_lst, char **envp)
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
				create_varenv(varenv_lst, name, value, false);
			free(name);
			free(value);
		}
		i++;
	}
}

void	init_minimalist_env(t_varenv **varenv_lst)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	create_varenv(varenv_lst, "PWD", pwd, false);
	create_varenv(varenv_lst, "SHLVL", "1", false);
	create_varenv(varenv_lst, "_", "/usr/bin/env", false);
	free(pwd);
}

t_varenv	*init_varenv(char **envp)
{
	t_varenv	*varenv_lst;

	varenv_lst = NULL;
	if (!envp || !*envp)
		init_minimalist_env(&varenv_lst);
	else
		init_existing_env(&varenv_lst, envp);
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

// Fonction pour dupliquer `envp`
char	**dup_env(char **envp)
{
	int		i;
	int		env_count;
	char	**new_env;

	env_count = 0;
	while (envp[env_count])
		env_count++;
	new_env = malloc((env_count + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < env_count)
	{
		new_env[i] = strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
