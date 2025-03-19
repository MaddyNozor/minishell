/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_var_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:37:21 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/19 16:25:51 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

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

char	*create_env_entry(t_data *data, t_varenv *varenv_lst)
{
	char	*temp;
	char	*entry;

	temp = ft_strjoin(varenv_lst->name, "=");
	if (!temp)
	{
		exit_with_error(data, "ft_strjoin", strerror(errno), 1);
		return (NULL);
	}
	entry = ft_strjoin(temp, varenv_lst->value);
	free(temp);
	if (!entry)
	{
		exit_with_error(data, "ft_strjoin", strerror(errno), 1);
		return (NULL);
	}
	return (entry);
}
static bool	alloc_env_entry(t_data *data, char **envp, t_varenv *varenv, int i)
{
	envp[i] = create_env_entry(data, varenv);
	if (!envp[i])
	{
		free_envp_on_error(envp, i);
		return (false);
	}
	return (true);
}

char	**convert_env_list_to_array(t_data *data, t_varenv *varenv_lst)
{
	int		count;
	char	**envp;
	int		i;

	count = count_env_vars(varenv_lst);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (exit_with_error(data, "malloc", strerror(errno), 1), NULL);
	i = 0;
	while (varenv_lst)
	{
		if (!varenv_lst->hiden && !alloc_env_entry(data, envp, varenv_lst, i))
			return (NULL);
		if (!varenv_lst->hiden)
			i++;
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

void	create_varenv(t_data *data, t_varenv **varenv_lst, t_varenv_data var_data)
{
	t_varenv	*new_node;
	// printf("🛠️ Création de la variable : %s=%s\n", var_data.name, var_data.value);

	new_node = malloc(sizeof(t_varenv));
	if (!new_node)
	{
		exit_with_error(data, "malloc", strerror(errno), 1);
		return;
	}
	new_node->name = ft_strdup(var_data.name);
	new_node->value = ft_strdup(var_data.value);
	new_node->hiden = var_data.hiden;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (!new_node->name || !new_node->value)
	{
		free_varenv_node(new_node);
		exit_with_error(data, "ft_strdup", strerror(errno), 1);
		return;
	}
	if (!*varenv_lst)
		*varenv_lst = new_node;
	else
		append_varenv_node(varenv_lst, new_node);
}
