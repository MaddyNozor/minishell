/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_var_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:18:44 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 12:03:08 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

char	*ft_expand(char *var_name, t_varenv *varenv)
{
	t_varenv	*current;

	current = varenv;
	while (current)
	{
		if (ft_strcmp(current->name, var_name) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

bool	ft_var_exists(char *var_name, t_varenv *varenv)
{
	t_varenv	*current;

	current = varenv;
	while (current)
	{
		if (ft_strcmp(current->name, var_name) == 0)
			return (true);
		current = current->next;
	}
	return (false);
}

void	replace_var(t_token *tok, char *new_content)
{
	free(tok->content);
	tok->content = NULL;
	if (new_content)
		tok->content = ft_strdup(new_content);
}

void	hvar(t_token *tok, t_queue *queue, t_cmd *current_cmd, t_varenv *varenv)
{
	char	*expanded_value;
	char	*var_name;
	t_data	*data;

	data = current_cmd->data;
	expanded_value = NULL;
	if (tok->content[0] == '$')
		var_name = tok->content + 1;
	else
		var_name = tok->content;
	if (ft_var_exists(var_name, varenv))
	{
		expanded_value = ft_expand(var_name, varenv);
		if (expanded_value)
		{
			enqueue_token(queue, expanded_value, data);
			current_cmd->argc++;
			free(expanded_value);
		}
	}
	tok->type = WORD;
}
