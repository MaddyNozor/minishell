/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 13:23:59 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

/* DESC: Allocate with malloc and return a new token.
 *  Init token->content with whatever is in 'content'
	->next and ->prev to NULL.
	->type with whatever is in 'type'
 * PARAM:   content: the content of the new element.
			type: type of token.
 * RETURN: the adress of new token. */
t_token	*ft_tok_new(void *content, int type)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->type = type;
	return (new);
}

/* DESC: Returns the last element of the list
 * PARAMETERS:
	lst: the start of the list
 * RETURN VALUES: Last element of the list */
t_token	*ft_toklast(t_token *lst)
{
	t_token	*current;

	if (lst == NULL)
		return (0);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

/* DESC: Add the 'new' element at the back of the list.
 * RETURN: No return value
 * PARAM:	lst: pointer adress of the first element of the list
 * 			new: pointer adress of the new element to add to the list */
void	ft_tokadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (new == NULL)
		return ;
	new->prev = NULL;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_toklast(*lst);
		new->prev = last;
		last->next = new;
	}
	return ;
}
t_token	*init_type_token_with_x_char_of_line(t_data *data, t_tok_params p)
{
	t_token	*new_token;
	char	*content;

	content = ft_substr(p.line, p.i, p.x);
	if (content == NULL)
	{
		data->lst_exit = 1;
		update_exit_status(data, 1);
		return (NULL);
	}
	new_token = ft_tok_new(content, p.type);
	if (new_token == NULL)
	{
		free(content);
		data->lst_exit = 1;
		update_exit_status(data, 1);
		return (NULL);
	}
	return (new_token);
}


void	free_token_list(t_token **list)
{
	t_token	*tmp_current;
	t_token	*tmp_next;

	if (!list || !*list)
		return ;
	tmp_current = *list;
	while (tmp_current)
	{
		tmp_next = tmp_current->next;
		free(tmp_current->content);
		free(tmp_current);
		tmp_current = tmp_next;
	}
	*list = NULL;
}
