/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:37:21 by sabellil          #+#    #+#             */
/*   Updated: 2025/01/24 13:38:23 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

void	append_varenv_node(t_varenv **varenv_lst, t_varenv *new_node)
{
	t_varenv	*current_node;

	if (!varenv_lst || !new_node)
		return ;
	current_node = *varenv_lst;
	while (current_node->next)
		current_node = current_node->next;
	current_node->next = new_node;
	new_node->prev = current_node;
}


void	free_varenv_node(t_varenv *node)
{
	if (node)
	{
		free(node->name);
		free(node->value);
		free(node);
	}
}

void	create_varenv(t_varenv **varenv_lst, char *name, char *value,
		bool hiden)
{
	t_varenv	*new_node;
	t_varenv	*current_node;

	new_node = malloc(sizeof(t_varenv));
	if (!new_node)
		return ;
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->hiden = hiden;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (!new_node->name || !new_node->value) //fonction free_node pour racourcir
	{
        free_varenv_node(new_node);
		return ;
	}
	if (!*varenv_lst) //si c'est le premier noeud, ajout a la tete de liste
		*varenv_lst = new_node;
	else //parcourir la liste pour ajouter a la fin
		append_varenv_node(varenv_lst, new_node);
}
