/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:11:52 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/20 19:03:21 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

static void	set_heredoc_delimiter(t_token **tok, t_redirection *redir, t_data *data)
{
	if ((*tok)->next)
	{
		*tok = (*tok)->next;
		if ((*tok)->type == WORD || (*tok)->type == VAR_ENV)
		{
			redir->file_name = ft_strdup((*tok)->content);
			if (!redir->file_name)
			{
				printf("bash: allocation error\n");
				data->lst_exit = 1;
				return ;
			}
			*tok = (*tok)->next;
		}
	}
}

static void	process_single_heredoc_token(t_token **tok, t_queue *queue, t_cmd *current_cmd, t_varenv *varenv)
{
	char	*expanded_value;
	t_data	*data;

	data = current_cmd->data;
	if ((*tok)->type == WORD)
	{
		if (!enqueue_token(queue, (*tok)->content, data))
			return ;
		current_cmd->argc++;
	}
	else if ((*tok)->type == VAR_ENV)
	{
		expanded_value = ft_expand((*tok)->content + 1, varenv);
		if (expanded_value)
		{
			if (!enqueue_token(queue, expanded_value, data))
			{
				free(expanded_value);
				return ;
			}
			current_cmd->argc++;
			free(expanded_value);
		}
	}
	*tok = (*tok)->next;
}

static void	process_heredoc_tokens(t_token **tok, t_cmd **current_cmd, t_varenv *varenv)
{
	t_data	*data;
	t_queue	*queue;
	t_node	*tmp;
	t_node	*to_free;

	data = (*current_cmd)->data;
	queue = init_queue(data);
	if (!queue)
	{
		printf("bash: allocation error\n");
		data->lst_exit = 1;
		return ;
	}
	while (*tok && ((*tok)->type == WORD || (*tok)->type == VAR_ENV))
		process_single_heredoc_token(tok, queue, *current_cmd, varenv);
	tmp = queue->head;
	while (tmp)
	{
		to_free = tmp;
		tmp = tmp->next;
		free(to_free->content);
		free(to_free);
	}
	free(queue);
}

static t_redirection	*create_heredoc_redirection(t_cmd **current_cmd, int redir_type)
{
	t_redirection	*redir;
	t_redirection	*tmp;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = redir_type;
	redir->next = NULL;
	tmp = (*current_cmd)->redirection;
	if (!tmp)
		(*current_cmd)->redirection = redir;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
	return (redir);
}

void	handle_heredoc(t_token *tok, t_cmd **current_cmd, t_varenv *varenv, int redir_type)
{
	t_redirection	*redir;
	t_data			*data;

	data = (*current_cmd)->data;
	redir = create_heredoc_redirection(current_cmd, redir_type);
	if (!redir)
	{
		printf("bash: allocation error\n");
		data->lst_exit = 1;
		return ;
	}
	set_heredoc_delimiter(&tok, redir, data);
	if (data->lst_exit == 1) // Si l'erreur d'allocation a été détectée, on ne continue pas
		return ;
	process_heredoc_tokens(&tok, current_cmd, varenv);
}

// static void	process_heredoc_tokens(t_token **tok, t_cmd **current_cmd, t_varenv *varenv)//TODO : A virer, car refactor
// {
// 	char	*expanded_value;
// 	t_data	*data;
// 	t_queue	*queue;

// 	data = (*current_cmd)->data;
// 	queue = init_queue(data);
// 	if (!queue)
// 	{
// 		printf("bash: allocation error\n");
// 		data->lst_exit = 1;
// 		return ;
// 	}
// 	while (*tok && ((*tok)->type == WORD || (*tok)->type == VAR_ENV))
// 	{
// 		if ((*tok)->type == WORD)
// 		{
// 			if (!enqueue_token(queue, (*tok)->content, data))
// 				return ;
// 			(*current_cmd)->argc++;
// 		}
// 		else if ((*tok)->type == VAR_ENV)
// 		{
// 			expanded_value = ft_expand((*tok)->content + 1, varenv);
// 			if (expanded_value)
// 			{
// 				if (!enqueue_token(queue, expanded_value, data))
// 				{
// 					free(expanded_value);
// 					return ;
// 				}
// 				(*current_cmd)->argc++;
// 				free(expanded_value);
// 			}
// 		}
// 		*tok = (*tok)->next;
// 	}
// } 
// void	handle_heredoc(t_token *tok, t_cmd **current_cmd, t_varenv *varenv, int redir_type)//TODO : A virer ca refactor
// {
// 	t_redirection	*redir;
// 	t_data			*data;

// 	data = (*current_cmd)->data;
// 	redir = malloc(sizeof(t_redirection));
// 	if (!redir)
// 	{
// 		printf("bash: allocation error\n");
// 		data->lst_exit = 1;
// 		return ;
// 	}
// 	redir->type = redir_type;
// 	redir->next = NULL;
// 	t_redirection *tmp = (*current_cmd)->redirection;
// 	if (!tmp)
// 		(*current_cmd)->redirection = redir;
// 	else
// 	{
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = redir;
// 	}
// 	set_heredoc_delimiter(&tok, redir, data);
// 	if (data->lst_exit == 1) // Si l'erreur d'allocation a été détectée, on ne continue pas
// 		return ;
// 	process_heredoc_tokens(&tok, current_cmd, varenv);
// }

// static void	process_heredoc_tokens(t_token **tok, t_cmd **current_cmd, t_varenv *varenv)
// {
// 	char	*expanded_value;

// 	while (*tok && ((*tok)->type == WORD || (*tok)->type == VAR_ENV))
// 	{
// 		if ((*tok)->type == WORD)
// 		{
// 			// printf("Heredoc argument stored: %s\n", (*tok)->content);
// 			enqueue_token(init_queue(), (*tok)->content);
// 			(*current_cmd)->argc++;
// 		}
// 		else if ((*tok)->type == VAR_ENV)
// 		{
// 			expanded_value = ft_expand((*tok)->content + 1, varenv);
// 			if (expanded_value)
// 			{
// 				// printf("Expanded heredoc argument: %s\n", expanded_value);
// 				enqueue_token(init_queue(), expanded_value);
// 				(*current_cmd)->argc++;
// 			}
// 			// else
// 			// 	printf("Heredoc expansion failed for: %s\n", (*tok)->content);
// 		}
// 		*tok = (*tok)->next;
// 	}
// }

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