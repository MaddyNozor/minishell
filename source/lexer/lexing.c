/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 15:20:19 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

// t_token	*lexer(char *line)
// {
// 	int		i;
// 	t_token	*head_of_list;
// 	t_token	*new_token;

// 	i = 0;
// 	new_token = NULL;
// 	head_of_list = NULL;
// 	while (line[i])
// 	{
// 		if (ft_is_whitespace(line[i]) == true)
// 			i++;
// 		else
// 		{
// 			new_token = create_token(line, i, new_token);
// 			if (new_token == NULL)
// 				return (ft_printf("bash: Cannot allocate memory\n"), NULL);
// 			ft_tokadd_back(&head_of_list, new_token);
// 			i += ft_strlen(new_token->content) - (new_token->quote_added * 2);
// 		}
// 	}
// 	if (check_lexing(head_of_list) == FAILURE)
// 		(ft_printf("Syntax error \n"), head_of_list = NULL);
// 	return (head_of_list);
// }

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

t_token	*lexer(t_data *data, char *line)
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
			new_token = create_token(data, line, i, new_token);
			if (new_token == NULL)
				return (return_malloc_error(data));
			ft_tokadd_back(&head_of_list, new_token);
			i += new_token->nb_chars_read;
		}
	}
	if (check_lexing(data, head_of_list) == FAILURE)
	{
		handle_lexer_syntax_error(data);
		head_of_list = NULL;
	}
	return (head_of_list);
}
