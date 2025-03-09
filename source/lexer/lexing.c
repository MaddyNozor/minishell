/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/09 16:26:01 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

/// tempo pour test
/// @param lst pointeur sur la tete de la liste
void	print_list(t_token *lst)
{
	int		i;
	t_token	*head_of_list;
	t_token	*new_token;

	while (lst)
	{
		printf("Token: %s, Type: %d nb_quotes: %d\n", lst->content, lst->type,
			lst->nb_quote);
		lst = lst->next;
	}
	printf("--List Printed--\n");
} 
// TODO a virer a terme

t_token	*lexer(char *line)
{
	int 	i;
	t_token *head_of_list;

	head_of_list = NULL;
	i = 0;
	while (line[i])
	{
		if (ft_is_whitespace(line[i]) == true)
			i++;
		else
		{
			new_token = create_token(line, i, new_token);
			ft_tokadd_back(&head_of_list, new_token);
			i = i + ft_strlen(new_token->content);
		}
	}
	print_list(head_of_list);
	if (check_lexing(head_of_list) == FAILURE)
	{
		head_of_list = NULL;
		ft_printf("Syntax error \n");
	}
	return (head_of_list);
}
