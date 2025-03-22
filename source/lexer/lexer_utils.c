/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:21:06 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 15:29:16 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

int	compute_word_len(t_data *data, char *line, int i, int *nb_pair_quote)
{
	int					len;
	t_quote_pair_ctx	ctx;

	len = 0;
	while (line[i + len] && have_to_close_tok(line[i + len]) == false)
	{
		if (line[i + len] == '\'' || line[i + len] == '\"')
		{
			ctx.len = &len;
			ctx.nb_pair_quote = nb_pair_quote;
			ctx.i = i;
			if (sub_ft_type_word(data, line, ctx) == NULL)
				return (-1);
		}
		len++;
	}
	return (len);
}

t_token	*free_token(t_token *tok)
{
	if (!tok)
		return (NULL);
	if (tok->content)
		free(tok->content);
	free(tok);
	return (NULL);
}
