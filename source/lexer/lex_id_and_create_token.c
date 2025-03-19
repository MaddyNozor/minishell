/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_id_and_create_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/19 17:23:04 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

// t_token	*token_type_operators(char *line, int i, t_token *new_token)
// {
// 	if (line[i] == '<')
// 	{
// 		if (line[i + 1] == '<')
// 			new_token = init_type_token_with_x_char_of_line(HEREDOC, new_token,
// 					2, line, i);
// 		else
// 			new_token = init_type_token_with_x_char_of_line(REDIRECT_IN,
// 					new_token, 1, line, i);
// 	}
// 	else if (line[i] == '>')
// 	{
// 		if (line[i + 1] == '>')
// 			new_token = init_type_token_with_x_char_of_line(APPEND_OUT,
// 					new_token, 2, line, i);
// 		else
// 			new_token = init_type_token_with_x_char_of_line(REDIRECT_OUT,
// 					new_token, 1, line, i);
// 	}
// 	else if (line[i] == '|')
// 		new_token = init_type_token_with_x_char_of_line(PIPE, new_token, 1,
// 				line, i);
// 	if (new_token == NULL)
// 		return (NULL);
// 	return (new_token);
// }

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

t_token	*token_type_varenv(char *line, int i, t_token *new_token)
{
	int	len_varenv;

	if (line[i + 1] == '?')
		new_token = init_type_token_with_x_char_of_line(VAR_ENV, 2, line, i);
	else if (line[i + 1] >= '0' && line[i + 1] <= '9')
		new_token = init_type_token_with_x_char_of_line(VAR_ENV, 2, line, i);
	else if (line[i + 1] != '_' && ft_isalpha(line[i + 1]) == FALSE)
		new_token = init_type_token_with_x_char_of_line(WORD, 1, line, i);
	else
	{
		len_varenv = 2;
		while (ft_isalnum(line[i + len_varenv]) || line[i + len_varenv] == '_')
			len_varenv++;
		new_token = init_type_token_with_x_char_of_line(VAR_ENV, len_varenv,
				line, i);
	}
	if (new_token == NULL)
		return (NULL);
	return (new_token);
}

char *sub_ft_type_word(int *len, int *nb_pair_quote, char *line, int i)
{
	char	type_of_quote;

	type_of_quote = line[i + *len];
	(*nb_pair_quote)++;
	(*len)++;
	while (line[i + *len] && line[i + *len] != type_of_quote)
		(*len)++;
	if (!line[i + *len])
	{
		ft_printf("Syntax Error\n");
		return (NULL);
	}
	return("");
}

t_token	*token_type_word(char *line, int i, t_token *new_token)
{
	int		len;
	int		nb_pair_quote;
	char *temp;
	char *temp2;

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
	ft_printf("new token content init type %s \n", new_token->content);
	new_token->nb_quote = nb_pair_quote;
    if (strchr(new_token->content, '$') != NULL && nb_pair_quote == 0)
    {
		ft_printf("new token content strchr %s \n", new_token->content);
        temp = ft_strjoin("\"", new_token->content);
        temp2 = ft_strjoin(temp, "\"");
        free(temp);
        new_token->content = temp2;
        new_token->nb_quote = 1;
    }
	return (new_token);
}

t_token	*create_token(char *line, int i, t_token *new_token)
{
	if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		new_token = token_type_operators(line, i, new_token);
	// else if (line[i] == '$')
	// 	new_token = token_type_varenv(line, i, new_token);
	else
		new_token = token_type_word(line, i, new_token);
	if (new_token == NULL)
		return (NULL);
	return (new_token);
}
