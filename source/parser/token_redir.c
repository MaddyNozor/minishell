/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:19:35 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/21 13:46:50 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

static int	set_redirection_file(t_token *tok, t_redirection *redir,
		t_varenv *varenv)
{
	char	*expanded_value;

	if (tok->type == WORD)
	{
		redir->file_name = ft_strdup(tok->content);
		return (1);
	}
	else if (tok->type == VAR_ENV)
	{
		expanded_value = ft_expand(tok->content + 1, varenv);
		if (!expanded_value)
			return (0);
		redir->file_name = expanded_value;
	}
	return (1);
}

static void	append_redirection(t_cmd **current_cmd, t_redirection *redir)
{
	t_redirection	*last_redir;

	if (!(*current_cmd)->redirection)
		(*current_cmd)->redirection = redir;
	else
	{
		last_redir = (*current_cmd)->redirection;
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = redir;
	}
}

static void	handle_redirect(t_token *tok, t_cmd **current_cmd, t_varenv *varenv,
		int redir_type)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return ;
	redir->type = redir_type;
	redir->next = NULL;
	if (tok->next && (tok->next->type == WORD || tok->next->type == VAR_ENV))
	{
		if (!set_redirection_file(tok->next, redir, varenv))
		{
			free(redir);
			return ;
		}
		tok = tok->next->next;
	}
	append_redirection(current_cmd, redir);
}

void	handle_redirections(t_token *tok, t_cmd **current_cmd, t_varenv *varenv)
{
	if (tok->type == REDIRECT_OUT)
		handle_redirect(tok, current_cmd, varenv, REDIRECT_OUT);
	else if (tok->type == APPEND_OUT)
		handle_redirect(tok, current_cmd, varenv, APPEND_OUT);
	else if (tok->type == REDIRECT_IN)
		handle_redirect(tok, current_cmd, varenv, REDIRECT_IN);
	else if (tok->type == HEREDOC)
		handle_heredoc(tok, current_cmd, varenv, HEREDOC);
}
