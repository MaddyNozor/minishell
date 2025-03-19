/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:00:05 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/19 13:28:33 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"
void	init_existing_env(t_varenv **varenv_lst, char **envp)
{
	char			*equal;
	char			*name;
	char			*value;
	int				i;
	t_varenv_data	var_data;

	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			name = ft_substr(envp[i], 0, equal - envp[i]);
			value = ft_strdup(equal + 1);
			if (name && value)
			{
				var_data = (t_varenv_data){name, value, false};
				create_varenv(NULL, varenv_lst, var_data);
			}
			free(name);
			free(value);
		}
		i++;
	}
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

// static bool	alloc_env_entry(t_data *data, char **new_env, char *env_entry, int index)//TODO : A virer a la fin, on lappelle jamais
// {
// 	new_env[index] = strdup(env_entry);
// 	if (!new_env[index])
// 	{
// 		free_tab(new_env);
// 		exit_with_error(data, "strdup", strerror(errno), 1);
// 		return (false);
// 	}
// 	return (true);
// }

// char	**dup_env(t_data *data, char **envp)//TODO : A virer a la fin, on lappelle jamais
// {
// 	int		i;
// 	int		env_count;
// 	char	**new_env;

// 	env_count = 0;
// 	while (envp[env_count])
// 		env_count++;
// 	new_env = malloc((env_count + 1) * sizeof(char *));
// 	if (!new_env)
// 	{
// 		exit_with_error(data, "malloc", strerror(errno), 1);
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (i < env_count)
// 	{
// 		if (!alloc_env_entry(data, new_env, envp[i], i))
// 			return (NULL);
// 		i++;
// 	}
// 	new_env[i] = NULL;
// 	return (new_env);
// }


// // Fonction pour dupliquer `envp`
// char	**dup_env(char **envp)//TODO : A virer a la fin (ajout de lst_exit)
// {
// 	int		i;
// 	int		env_count;
// 	char	**new_env;

// 	env_count = 0;
// 	while (envp[env_count])
// 		env_count++;
// 	new_env = malloc((env_count + 1) * sizeof(char *));
// 	if (!new_env)
// 		return (NULL);
// 	i = 0;
// 	while (i < env_count)
// 	{
// 		new_env[i] = strdup(envp[i]);
// 		i++;
// 	}
// 	new_env[i] = NULL;
// 	return (new_env);
// }
