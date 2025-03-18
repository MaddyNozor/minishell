/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_var_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:18:44 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/18 12:06:40 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

char	*ft_expand(char *var_name, t_varenv *varenv)
{
	t_varenv	*current;

	current = varenv;
	// printf("Expansion de %s...\n", var_name);
	while (current)
	{
		// printf("Comparaison avec %s\n", current->name);
		if (ft_strcmp(current->name, var_name) == 0)
		{
			// printf("Valeur trouvee: %s = %s\n", var_name, current->value);
			return (ft_strdup(current->value));
		}
		current = current->next;
	}
	// printf("Variable %s introuvable dans varenv_lst\n", var_name);
	return (NULL);
}

bool	ft_var_exists(char *var_name, t_varenv *varenv)
{
	t_varenv	*current;

	current = varenv;
	// printf("Recherche de la variable: %s\n", var_name);
	while (current)
	{
		if (ft_strcmp(current->name, var_name) == 0)
		{
			// printf("Variable %s trouvee !\n", var_name);
			return (true);
		}
		current = current->next;
	}
	// printf("Variable %s non trouvee\n", var_name);
	return (false);
}

void	replace_var(t_token *tok, char *new_content)
{
	free(tok->content);
	tok->content = NULL;
	if (new_content)
		tok->content = ft_strdup(new_content);
}
void	handle_var_env(t_token *tok, t_queue *queue, t_cmd *current_cmd, t_varenv *varenv)
{
	char	*expanded_value;
	char	*var_name;

	expanded_value = NULL;
	if (tok->content[0] == '$')
		var_name = tok->content + 1;
	else
		var_name = tok->content;
	if (ft_strcmp(var_name, "?") == 0)
		expanded_value = get_exit_status(varenv);
	else if (ft_var_exists(var_name, varenv))
		expanded_value = ft_expand(var_name, varenv);
	if (expanded_value)
	{
		enqueue_token(queue, expanded_value);
		current_cmd->argc++;
		free(expanded_value);
	}
	tok->type = WORD;
}


// void	handle_var_env(t_token *tok, t_queue *queue, t_cmd *current_cmd, t_varenv *varenv)
// {
// 	char	*expanded_value;
// 	char	*var_name;

// 	expanded_value = NULL;
// 	if (tok->content[0] == '$')
// 		var_name = tok->content + 1;
// 	else
// 		var_name = tok->content;

// 	if (ft_var_exists(var_name, varenv))
// 	{
// 		expanded_value = ft_expand(var_name, varenv);
// 		if (expanded_value)
// 		{
// 			enqueue_token(queue, expanded_value); // On ajoute directement la valeur expandée
// 			current_cmd->argc++; // Incrémente le nombre d'arguments
// 			free(expanded_value);
// 		}
// 	}
// 	tok->type = WORD; // Change en WORD pour ne pas être re-traité
// }
