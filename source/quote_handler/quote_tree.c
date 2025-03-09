/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/09 16:03:33 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

// //Fonction test, a virer (ou conserver pour l'historique et 
// //l'explication du chemin du code)
// char	*ft_fake_expand_varenv(char *var_found)
// {
// 	char *prefix = "[VARENV:";
// 	char *suffix = "]";
// 	char *temp;
// 	char *fake_var_env;

// 	temp = ft_strjoin(prefix, var_found);
// 	fake_var_env = ft_strjoin(temp, suffix);
// 	free(temp);
// 	return (fake_var_env);
// }

char	*ft_expand(char *var_name, t_varenv *varenv)
{
	t_varenv	*current;

	current = varenv;
	printf("Expansion de %s...\n", var_name);
	while (current)
	{
		printf("Comparaison avec %s\n", current->name);
		if (ft_strcmp(current->name, var_name) == 0)
		{
			printf("Valeur trouvee: %s = %s\n", var_name, current->value);
			return (ft_strdup(current->value));
		}
		current = current->next;
	}
	printf("Variable %s introuvable dans varenv_lst\n", var_name);
	return (NULL);
}

bool	ft_var_exists(char *var_name, t_varenv *varenv)
{
	t_varenv	*current;

	current = varenv;
	printf("Recherche de la variable: %s\n", var_name);
	while (current)
	{
		if (ft_strcmp(current->name, var_name) == 0)
		{
			printf("Variable %s trouvee !\n", var_name);
			return (true);
		}
		current = current->next;
	}
	printf("Variable %s non trouvee\n", var_name);
	return (false);
}

char	*ft_expand_varenv(char *var_found, t_varenv *varenv)
{
	char	*expanded_value;
	char	*var_name;

	expanded_value = NULL;
	var_name = var_found + 1;
	if (ft_var_exists(var_name, varenv))
		expanded_value = ft_expand(var_name, varenv);
	return (expanded_value);
}

/*
void	handle_var_env(t_token *tok, t_queue *queue, t_cmd *current_cmd,
	t_varenv *varenv)
{
char	*expanded_value;
char	*var_name;

expanded_value = NULL;
printf("Handling VAR_ENV token: %s\n", tok->content);
if (tok->content[0] == '$')
	var_name = tok->content + 1; // supprime le '$' pour la recherche
else
	var_name = tok->content;
if	(ft_var_exists(var_name, varenv))
{
	expanded_value = ft_expand(var_name, varenv);
	if (expanded_value)
	{
		replace_var(tok, expanded_value);
		tok->type = WORD;
		printf("Expanded value: %s\n", expanded_value);
		handle_token_word(queue, &tok, current_cmd);
		free(expanded_value);
	}
}
else
{
	replace_var(tok, NULL);
	tok->type = WORD;
}
*/
