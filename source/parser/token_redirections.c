/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:19:35 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/08 18:08:55 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

static void	handle_heredoc(t_token *tok, t_cmd **current_cmd, t_varenv *varenv, int redir_type)
{
	t_redirection	*redir;
	char			*expanded_value;

	// Création de la structure de redirection
	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return ;
	redir->type = redir_type; // Stocke le type de redirection
	redir->next = NULL;
	(*current_cmd)->redirection = redir;
		// Lier la redirection à la commande actuelle
	// Vérification du token suivant (après "<<")
	if (tok->next)
	{
		tok = tok->next; // Passer au token suivant
		// Si c'est un WORD ou un VAR_ENV, on le stocke en filename (mais sans expansion pour VAR_ENV)
		if (tok->type == WORD || tok->type == VAR_ENV)
		{
			redir->file_name = ft_strdup(tok->content);
			printf("Heredoc delimiter set to: %s\n", redir->file_name);
			tok = tok->next;
				// Passer au token suivant après le fichier de redirection
		}
	}
	// Traitement des tokens suivants tant que c'est un WORD ou VAR_ENV
	while (tok && (tok->type == WORD || tok->type == VAR_ENV))
	{
		if (tok->type == WORD)
		{
			printf("Heredoc argument stored: %s\n", tok->content);
			enqueue_token(init_queue(), tok->content);
			(*current_cmd)->argc++;
		}
		else if (tok->type == VAR_ENV)
		{
			expanded_value = ft_expand(tok->content + 1, varenv);
			if (expanded_value)
			{
				printf("Expanded heredoc argument: %s\n", expanded_value);
				enqueue_token(init_queue(), expanded_value);
				(*current_cmd)->argc++;
			}
			else
			{
				printf("Heredoc expansion failed for: %s\n", tok->content);
			}
		}
		tok = tok->next;
	}
}
static void	handle_redirect(t_token *tok, t_cmd **current_cmd, t_varenv *varenv, int redir_type)
{
	t_redirection	*redir;
	t_redirection	*last_redir;
	char			*filename;
	char			*expanded_value;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return ;
	redir->type = redir_type;
	redir->next = NULL;

	if (tok->next && (tok->next->type == WORD || tok->next->type == VAR_ENV))
	{
		if (tok->next->type == WORD)
		{
			filename = ft_strdup(tok->next->content);
			redir->file_name = filename;
			printf("Redirecting to file: %s\n", filename);
		}
		else if (tok->next->type == VAR_ENV)
		{
			expanded_value = ft_expand(tok->next->content + 1, varenv);
			if (expanded_value)
			{
				redir->file_name = expanded_value;
				printf("Redirecting to expanded value: %s\n", expanded_value);
			}
			else
			{
				fprintf(stderr, "bash: %s: ambiguous redirect\n",
						tok->next->content);
				free(redir);
				return;
			}
		}
		tok = tok->next->next;
	}

	// 🔥 Chaînage correct : ajouter à la fin au lieu d'écraser l'existant
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

void	handle_redirections(t_token *tok, t_cmd **current_cmd, t_varenv *varenv)
{
	if (tok->type == REDIRECT_OUT)
		handle_redirect(tok, current_cmd, varenv, REDIR_OUT);
	else if (tok->type == APPEND_OUT)
		handle_redirect(tok, current_cmd, varenv, REDIR_APPEND);
	else if (tok->type == REDIRECT_IN)
		handle_redirect(tok, current_cmd, varenv, REDIR_IN);
	else if (tok->type == HEREDOC)
		handle_heredoc(tok, current_cmd, varenv, REDIR_HEREDOC);
}
