/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:19:35 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/03 12:46:12 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	handle_heredoc(t_token *tok, t_cmd **current_cmd, t_varenv *varenv)
{
	t_redirection	*redir;
	char			*expanded_value;

	// Création de la structure de redirection
	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return ;
	redir->type = HEREDOC; // Stocke le type de redirection
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

void	handle_redirect_out(t_token *tok, t_cmd **current_cmd, t_varenv *varenv)
{
	t_redirection	*redir;
	char			*filename;
	char			*expanded_value;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return ;
	redir->type = REDIR_OUT;
	redir->next = NULL;
	(*current_cmd)->redirection = redir;
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
				return ;
			}
		}
		tok = tok->next->next;
		while (tok && tok->type == WORD)
		{
			printf("OUI token est un token_word a stocker en queue\n");
			enqueue_token(init_queue(), tok->content);
			(*current_cmd)->argc++;
			printf("Added argument: %s, new argc: %d\n", tok->content,
					(*current_cmd)->argc);
		}
	}
	else
		handle_tokens(tok->next, current_cmd, varenv);
}

void	handle_redirections(t_token *tok, t_cmd **current_cmd, t_varenv *varenv)
{
	// On traite chaque type de redirection en fonction du type du token
	if (tok->type == REDIRECT_OUT) //OK
		handle_redirect_out(tok, current_cmd, varenv);
	else if (tok->type == APPEND_OUT) //OK
	{
		// handle_append_out(tok, current_cmd, varenv); 
			// A supprimer apres verif que > et >> se traitent de la meme facon
		handle_redirect_out(tok, current_cmd, varenv);
	}
	else if (tok->type == REDIRECT_IN) //TODO: verifier comportement
	{
		printf("Je gere < apres\n");
		// handle_redirect_in(tok, current_cmd, varenv);
	}
	else if (tok->type == HEREDOC) //OK
		handle_heredoc(tok, current_cmd, varenv);
}
