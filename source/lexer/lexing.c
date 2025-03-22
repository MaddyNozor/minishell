/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 15:38:28 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

t_token	*return_malloc_error(t_data *data)
{
	ft_printf("bash: Cannot allocate memory\n");
	data->lst_exit = 1;
	update_exit_status(data, 1);
	return (NULL);
}

void	handle_lexer_syntax_error(t_data *data)
{
	ft_printf("Syntax error\n");
	data->lst_exit = 2;
	update_exit_status(data, 2);
}

t_token	*check_lexer_and_cleanup(t_data *data, t_token **head)
{
	if (check_lexing(data, *head) == FAILURE)
	{
		handle_lexer_syntax_error(data);
		free_token_list(head);
		return (NULL);
	}
	return (*head);
}

t_token	*lexer(t_data *data, char *line)
{
	int		i;
	t_token	*head;
	t_token	*new_token;

	i = 0;
	head = NULL;
	while (line[i])
	{
		if (ft_is_whitespace(line[i]))
			i++;
		else
		{
			new_token = create_token(data, line, i, NULL);
			if (!new_token)
			{
				free_token_list(&head);
				return (return_malloc_error(data));
			}
			ft_tokadd_back(&head, new_token);
			i += new_token->nb_chars_read;
		}
	}
	return (check_lexer_and_cleanup(data, &head));
}
