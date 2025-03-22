/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 15:29:22 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

int	return_lexer_syntax_error(t_data *data)
{
	data->lst_exit = 2;
	update_exit_status(data, 2);
	return (FAILURE);
}

int	free_and_return_syntax_error(t_data *data, t_token **lst)
{
	free_token_list(lst);
	data->lst_exit = 2;
	update_exit_status(data, 2);
	return (FAILURE);
}

int	check_lexing(t_data *data, t_token *head_of_list)
{
	t_token	*current_token;
	t_token	*last_token;

	if (head_of_list == NULL)
		return (SUCCESS);
	if (head_of_list->type == PIPE)
		return (return_lexer_syntax_error(data));
	last_token = ft_toklast(head_of_list);
	if (is_an_operator(last_token->type) == true)
		return (return_lexer_syntax_error(data));
	current_token = head_of_list;
	while (current_token->next != NULL)
	{
		if (is_an_operator(current_token->type) == true
			&& is_an_operator(current_token->next->type) == true)
			return (free_and_return_syntax_error(data, &head_of_list));
		current_token = current_token->next;
	}
	return (SUCCESS);
}
