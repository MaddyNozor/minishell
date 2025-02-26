/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:00:05 by sabellil          #+#    #+#             */
/*   Updated: 2025/02/21 18:43:15 by mairivie         ###   ########.fr       */
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
	return (varenv_lst);
}

// //TEST INIT_SHELL a utiliser avec init_shell.c et init_shell_utils.c
// void print_varenv(t_varenv *varenv_lst)
// {
//     t_varenv *current = varenv_lst;
//     while (current)
//     {
//         printf("%s=%s\n", current->name, current->value);
//         current = current->next;
//     }
// }

// void free_varenv(t_varenv *varenv_lst)
// {
//     t_varenv *current = varenv_lst;
//     t_varenv *next;
//     while (current)
//     {
//         next = current->next;
//         free(current->name);
//         free(current->value);
//         free(current);
//         current = next;
//     }
// }

// int main(int argc, char **argv, char **envp)
// {
//     t_varenv *varenv_lst;

//     (void)argc; // On ignore les arguments du programme
//     (void)argv;

//     if (envp[0] == NULL) // Cas où `env -i` est utilisé (environnement vide)
//     {
//         printf("Lancement avec environnement vide (env -i).\n");
//         varenv_lst = init_varenv(NULL);
	// Appel avec NULL pour un environnement minimaliste
//     }
//     else
//     {
//         printf("Lancement avec l'environnement actuel.\n");
//         varenv_lst = init_varenv(envp); // Appel avec l'environnement fourni
//     }

//     // Affiche les variables d'environnement
//     printf("Variables d'environnement :\n");
//     print_varenv(varenv_lst);

//     // Libère la mémoire allouée
//     free_varenv(varenv_lst);

//     return (0);
// }