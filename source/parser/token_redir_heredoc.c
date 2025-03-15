/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:11:52 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/15 15:31:00 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

static void	set_heredoc_delimiter(t_token **tok, t_redirection *redir)
{
	if ((*tok)->next)
	{
		*tok = (*tok)->next;
		if ((*tok)->type == WORD || (*tok)->type == VAR_ENV)
		{
			redir->file_name = ft_strdup((*tok)->content);
			// printf("Heredoc delimiter set to: %s\n", redir->file_name);
			*tok = (*tok)->next;
		}
	}
}

static void	process_heredoc_tokens(t_token **tok, t_cmd **current_cmd, t_varenv *varenv)
{
	char	*expanded_value;

	while (*tok && ((*tok)->type == WORD || (*tok)->type == VAR_ENV))
	{
		if ((*tok)->type == WORD)
		{
			// printf("Heredoc argument stored: %s\n", (*tok)->content);
			enqueue_token(init_queue(), (*tok)->content);
			(*current_cmd)->argc++;
		}
		else if ((*tok)->type == VAR_ENV)
		{
			expanded_value = ft_expand((*tok)->content + 1, varenv);
			if (expanded_value)
			{
				// printf("Expanded heredoc argument: %s\n", expanded_value);
				enqueue_token(init_queue(), expanded_value);
				(*current_cmd)->argc++;
			}
			// else
			// 	printf("Heredoc expansion failed for: %s\n", (*tok)->content);
		}
		*tok = (*tok)->next;
	}
}

void	handle_heredoc(t_token *tok, t_cmd **current_cmd, t_varenv *varenv, int redir_type)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return ;
	redir->type = redir_type;
	redir->next = NULL;
	// (*current_cmd)->redirection = redir;

	t_redirection *tmp = (*current_cmd)->redirection;
	if (!tmp)
		(*current_cmd)->redirection = redir;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
		set_heredoc_delimiter(&tok, redir);
	process_heredoc_tokens(&tok, current_cmd, varenv);
}

// void	handle_heredoc(t_token *tok, t_cmd **current_cmd, t_varenv *varenv, int redir_type)//Ca fonctionn mais c'est trop long, a virer a la fin
// {
// 	t_redirection	*redir;
// 	char			*expanded_value;

// 	// Création de la structure de redirection
// 	redir = malloc(sizeof(t_redirection));
// 	if (!redir)
// 		return ;
// 	redir->type = redir_type; // Stocke le type de redirection
// 	redir->next = NULL;
// 	(*current_cmd)->redirection = redir;
// 		// Lier la redirection à la commande actuelle
// 	// Vérification du token suivant (après "<<")
// 	if (tok->next)
// 	{
// 		tok = tok->next; // Passer au token suivant
// 		// Si c'est un WORD ou un VAR_ENV, on le stocke en filename (mais sans expansion pour VAR_ENV)
// 		if (tok->type == WORD || tok->type == VAR_ENV)
// 		{
// 			redir->file_name = ft_strdup(tok->content);
// 			printf("Heredoc delimiter set to: %s\n", redir->file_name);
// 			tok = tok->next;
// 				// Passer au token suivant après le fichier de redirection
// 		}
// 	}
// 	// Traitement des tokens suivants tant que c'est un WORD ou VAR_ENV
// 	while (tok && (tok->type == WORD || tok->type == VAR_ENV))
// 	{
// 		if (tok->type == WORD)
// 		{
// 			printf("Heredoc argument stored: %s\n", tok->content);
// 			enqueue_token(init_queue(), tok->content);
// 			(*current_cmd)->argc++;
// 		}
// 		else if (tok->type == VAR_ENV)
// 		{
// 			expanded_value = ft_expand(tok->content + 1, varenv);
// 			if (expanded_value)
// 			{
// 				printf("Expanded heredoc argument: %s\n", expanded_value);
// 				enqueue_token(init_queue(), expanded_value);
// 				(*current_cmd)->argc++;
// 			}
// 			else
// 			{
// 				printf("Heredoc expansion failed for: %s\n", tok->content);
// 			}
// 		}
// 		tok = tok->next;
// 	}
// }