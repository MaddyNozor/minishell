/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/20 18:30:17 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

// /// tempo pour test
// /// @param lst pointeur sur la tete de la liste
// void	print_list(t_token *lst)
// {
// 	while (lst)
// 	{
// 		printf("Token: %s, Type: %d\n", lst->content, lst->type);
// 		lst = lst->next;
// 	}
// 	printf("--List Printed--\n");
// } //TODO  pour test a virer a terme

t_token	*lexer(char *line)
{
	int		i;
	t_token	*head_of_list;
	t_token	*new_token;

	i = 0;
	new_token = NULL;
	head_of_list = NULL;
	while (line[i])
	{
		if (ft_is_whitespace(line[i]) == true)
			i++;
		else
		{
			new_token = create_token(line, i, new_token);
			if (new_token == NULL)
				return (ft_printf("bash: Cannot allocate memory\n"), NULL);
			ft_tokadd_back(&head_of_list, new_token);
			i += ft_strlen(new_token->content) - (new_token->quote_added * 2);
		}
	}
	if (check_lexing(head_of_list) == FAILURE)
		(ft_printf("Syntax error \n"), head_of_list = NULL);
	return (head_of_list);
}
