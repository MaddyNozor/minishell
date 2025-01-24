/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/01/24 17:13:22 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/lexing.h"
# include "../include/init_shell.h"

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

	new = (t_token *)malloc(sizeof(t_token) * 1);
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
    new->prev = NULL;
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