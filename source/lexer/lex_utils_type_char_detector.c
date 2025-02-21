/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils_type_char_detector.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/02/21 18:44:53 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

bool	ft_is_whitespace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (true);
	else
		return (false);
}

int	have_to_close_tok(char c)
{
	if (c == '<' || c == '|' || c == '>' || c == '$'
		|| ft_is_whitespace(c) == true)
		return (true);
	return (false);
}

int	is_an_operator(int type)
{
	if (type == PIPE || type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == APPEND_OUT || type == HEREDOC)
		return (true);
	return (false);
}
