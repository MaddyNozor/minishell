/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/09 16:22:09 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

int	check_lexing(t_token *head_of_list)
{
	t_token	*current_token;
	t_token	*last_token;

	if (head_of_list == NULL)
		return (SUCCESS);
	else if (head_of_list->type == PIPE)
		return (FAILURE);
	last_token = ft_toklast(head_of_list);
	if (is_an_operator(last_token->type) == true)
		return (FAILURE);
	current_token = head_of_list;
	while (current_token->next != NULL)
	{
		if (is_an_operator(current_token->type) == true
			&& is_an_operator(current_token->next->type) == true)
		{
			free_token_list(head_of_list);
			return (FAILURE);
		}
		current_token = current_token->next;
	}
	return (SUCCESS);
}
