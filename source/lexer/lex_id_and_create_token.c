/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_id_and_create_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 15:21:56 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

t_token	*token_type_operators(t_data *data, char *line, int i,
		t_token *new_token)
{
	int				size_content;
	int				type;
	t_tok_params	p;

	type = ft_type_detector(line, i);
	size_content = ft_size_according_to_type(type);
	p.type = type;
	p.x = size_content;
	p.line = line;
	p.i = i;
	new_token = init_type_token_with_x_char_of_line(data, p);
	if (new_token == NULL)
	{
		ft_printf("bash: Cannot allocate memory\n");
		data->lst_exit = 1;
		update_exit_status(data, 1);
		return (NULL);
	}
	return (new_token);
}

char	*sub_ft_type_word(t_data *data, char *line, t_quote_pair_ctx ctx)
{
	char	type_of_quote;

	type_of_quote = line[ctx.i + *ctx.len];
	(*ctx.nb_pair_quote)++;
	(*ctx.len)++;
	while (line[ctx.i + *ctx.len] && line[ctx.i + *ctx.len] != type_of_quote)
		(*ctx.len)++;
	if (!line[ctx.i + *ctx.len])
	{
		printf("bash: syntax error\n");
		data->lst_exit = 2;
		update_exit_status(data, 2);
		return (NULL);
	}
	return ("");
}

int	add_quotes_to_content(t_data *data, t_token *token)
{
	char	*temp;
	char	*quoted_content;

	if (!token || !token->content)
		return (FAILURE);
	temp = ft_strjoin("\"", token->content);
	if (!temp)
	{
		data->lst_exit = 1;
		update_exit_status(data, 1);
		return (FAILURE);
	}
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
	int				len;
	int				nb_pair_quote;
	t_tok_params	p;

	nb_pair_quote = 0;
	len = compute_word_len(data, line, i, &nb_pair_quote);
	if (len == -1)
		return (NULL);
	p.type = WORD;
	p.x = len;
	p.line = line;
	p.i = i;
	new_token = init_type_token_with_x_char_of_line(data, p);
	if (!new_token)
		return (NULL);
	new_token->nb_quote = nb_pair_quote;
	new_token->quote_added = false;
	if (ft_strchr(new_token->content, '$') != NULL && nb_pair_quote == 0)
	{
		if (add_quotes_to_content(data, new_token) == FAILURE)
			return (free_token(new_token));
		new_token->quote_added = true;
	}
	new_token->nb_chars_read = len;
	return (new_token);
}

t_token	*create_token(t_data *data, char *line, int i, t_token *new_token)
{
	if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		new_token = token_type_operators(data, line, i, new_token);
	else
		new_token = token_type_word(data, line, i, new_token);
	if (new_token == NULL)
		return (NULL);
	return (new_token);
}
