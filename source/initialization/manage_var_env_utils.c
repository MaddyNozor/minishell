/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_var_env_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:13:45 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 11:38:50 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	free_varenv(t_varenv *varenv_lst)
{
	t_varenv	*current;
	t_varenv	*next;

	current = varenv_lst;
	while (current)
	{	
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
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

void	free_cmd_list(t_cmd *list)
{
	t_cmd			*tmp;
	t_redirection	*redir_tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->value);
		while (tmp->redirection)
		{
			redir_tmp = tmp->redirection;
			tmp->redirection = tmp->redirection->next;
			free(redir_tmp->file_name);
			free(redir_tmp);
		}
		free_tab(tmp->argv);
		free(tmp);
	}
}

void	free_envp_on_error(char **envp, int i)
{
	while (i > 0)
		free(envp[--i]);
	free(envp);
}

int	count_env_vars(t_varenv *varenv_lst)
{
	int	count;

	count = 0;
	while (varenv_lst)
	{
		if (!varenv_lst->hiden)
			count++;
		varenv_lst = varenv_lst->next;
	}
	return (count);
}
