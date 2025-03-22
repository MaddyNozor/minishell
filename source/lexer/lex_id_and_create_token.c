/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_id_and_create_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 12:45:37 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

t_token	*token_type_operators(char *line, int i, t_token *new_token)
{
	int	size_content;
	int	type;

	type = ft_type_detector(line, i);
	size_content = ft_size_according_to_type(type);
	new_token = init_type_token_with_x_char_of_line(type, size_content, line,
			i);
	if (new_token == NULL)
		return (NULL);
	return (new_token);
}

char	*sub_ft_type_word(t_data *data, int *len, int *nb_pair_quote, char *line, int i)
{
	char	type_of_quote;

	type_of_quote = line[i + *len];
	(*nb_pair_quote)++;
	(*len)++;
	while (line[i + *len] && line[i + *len] != type_of_quote)
		(*len)++;
	if (!line[i + *len])
	{
		{
			perror("Syntax error\n");
			update_exit_status(data, 1);
			return (NULL);
		}
	}
	return ("");
}

int	add_quotes_to_content(t_token *token)
{
	char	*temp;
	char	*quoted_content;

	if (!token || !token->content)
		return (FAILURE);
	temp = ft_strjoin("\"", token->content);
	if (!temp)
		return (FAILURE);
	quoted_content = ft_strjoin(temp, "\"");
	free(temp);
	if (!quoted_content)
		return (FAILURE);
	free(token->content);
	token->content = quoted_content;
	token->nb_quote = 1;
	return (SUCCESS);
}

t_token	*token_type_word(t_data *data, char *line, int i, t_token *new_token)
{
	int	len;
	int	nb_pair_quote;

	len = 0;
	nb_pair_quote = 0;
	while (line[i + len] && have_to_close_tok(line[i + len]) == false)
	{
		if (line[i + len] == '\'' || line[i + len] == '\"')
			if (sub_ft_type_word(&len, &nb_pair_quote, line, i) == NULL)
				return (NULL);
		len++;
	}
	new_token = init_type_token_with_x_char_of_line(WORD, len, line, i);
	new_token->nb_quote = nb_pair_quote;
	if (ft_strchr(new_token->content, '$') != NULL && nb_pair_quote == 0)
	{
		if (add_quotes_to_content(new_token) == FAILURE)
			return (NULL);
		new_token->quote_added = true;
	}
	return (new_token);
}

t_token	*create_token(t_data *data, char *line, int i, t_token *new_token)
{
	if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		new_token = token_type_operators(line, i, new_token);
	else
		new_token = token_type_word(data, line, i, new_token);
	if (new_token == NULL)
		return (NULL);
	return (new_token);
}
