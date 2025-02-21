/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_var_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:37:21 by sabellil          #+#    #+#             */
/*   Updated: 2025/02/21 18:44:52 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

// char	**convert_env_list_to_array(t_varenv *varenv_lst)//avirer
// {
// 	int		count;
// 	char	**envp;
// 	int		i;
// 	char	*temp;

// 	count = count_env_vars(varenv_lst);
// 	envp = malloc(sizeof(char *) * (count + 1));
// 	i = 0;
// 	if (!envp)
// 		return (NULL);
// 	while (varenv_lst)
// 	{
// 		if (!varenv_lst->hiden)
// 		{
// 			temp = ft_strjoin(varenv_lst->name, "=");
// 			if (!temp)
// 				return (NULL);
// 			envp[i] = ft_strjoin(temp, varenv_lst->value);
// 			free(temp);
// 			if (!envp[i])
// 			{
// 				while (i > 0)
// 					free(envp[--i]);
// 				free(envp);
// 				return (NULL);
// 			}
// 			i++;
// 		}
// 		varenv_lst = varenv_lst->next;
// 	}
// 	envp[i] = (NULL);
// 	return (envp);
// }

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

char	*create_env_entry(t_varenv *varenv_lst)
{
	char	*temp;
	char	*entry;

	temp = ft_strjoin(varenv_lst->name, "=");
	if (!temp)
		return (NULL);
	entry = ft_strjoin(temp, varenv_lst->value);
	free(temp);
	return (entry);
}

char	**convert_env_list_to_array(t_varenv *varenv_lst)
{
	int		count;
	char	**envp;
	int		i;

	count = count_env_vars(varenv_lst);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (varenv_lst)
	{
		if (!varenv_lst->hiden)
		{
			envp[i] = create_env_entry(varenv_lst);
			if (!envp[i])
				return (free_envp_on_error(envp, i), NULL);
			i++;
		}
		varenv_lst = varenv_lst->next;
	}
	envp[i] = NULL;
	return (envp);
}

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

void	create_varenv(t_varenv **varenv_lst, char *name, char *value,
		bool hiden)
{
	t_varenv	*new_node;

	new_node = malloc(sizeof(t_varenv));
	if (!new_node)
		return ;
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->hiden = hiden;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (!new_node->name || !new_node->value)
	{
		free_varenv_node(new_node);
		return ;
	}
	if (!*varenv_lst)
		*varenv_lst = new_node;
	else
		append_varenv_node(varenv_lst, new_node);
}
