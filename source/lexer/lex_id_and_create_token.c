/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_id_and_create_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/02/21 15:55:20 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

t_token	*token_type_operators(char *line, int i, t_token *new_token)
{
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			new_token = init_type_token_with_x_char_of_line(HEREDOC, new_token,
					2, line, i);
		else
			new_token = init_type_token_with_x_char_of_line(REDIRECT_IN,
					new_token, 1, line, i);
	}
	else if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			new_token = init_type_token_with_x_char_of_line(APPEND_OUT,
					new_token, 2, line, i);
		else
			new_token = init_type_token_with_x_char_of_line(REDIRECT_OUT,
					new_token, 1, line, i);
	}
	else if (line[i] == '|')
		new_token = init_type_token_with_x_char_of_line(PIPE, new_token, 1,
				line, i);
	if (new_token == NULL)
		return (NULL);
	return (new_token);
}

t_token	*token_type_varenv(char *line, int i, t_token *new_token)
{
	int	len_varenv;

	if (line[i + 1] == '?')
		new_token = init_type_token_with_x_char_of_line(LAST_EXIT, new_token, 2,
				line, i);
	else if (line[i + 1] >= '0' && line[i + 1] <= '9')
		new_token = init_type_token_with_x_char_of_line(VAR_ENV, new_token, 2,
				line, i);
	else if (line[i + 1] != '_' && ft_isalpha(line[i + 1]) == FALSE)
		new_token = init_type_token_with_x_char_of_line(WORD, new_token, 1,
				line, i);
	else
	{
		len_varenv = 2;
		while (ft_isalnum(line[i + len_varenv]) || line[i + len_varenv] == '_')
			len_varenv++;
		new_token = init_type_token_with_x_char_of_line(VAR_ENV, new_token,
				len_varenv, line, i);
	}
	if (new_token == NULL)
		return (NULL);
	return (new_token);
}

t_token	*token_type_word(char *line, int i, t_token *new_token)
{
	int		len;
	char	type_of_quote;

	len = 0;
	while (line[i + len] && have_to_close_tok(line[i + len]) == false)
	{
		if (line[i + len] == '\'' || line[i + len] == '\"')
		{
			type_of_quote = line[i + len];
			ft_printf("type of quote: %c\n", type_of_quote);
			len++;
			while (line[i + len] && line[i + len] != type_of_quote)
				len++;
			if (!line[i + len])
				return (ft_printf("rajoute une quote !\n"), NULL);
		}
		len++;
	}
	new_token = init_type_token_with_x_char_of_line(WORD, new_token, len, line,
			i);
	return (new_token);
}

t_token	*create_token(char *line, int i, t_token *new_token)
{
	if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		new_token = token_type_operators(line, i, new_token);
	else if (line[i] == '$')
		new_token = token_type_varenv(line, i, new_token);
	else
		new_token = token_type_word(line, i, new_token);
	return (new_token);
}
