/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:02:30 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/20 16:38:09 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	ft_unset_utils(t_varenv *current, t_data *data)
{
	t_varenv *temp;

	temp = current;
	if (!current->prev && current->next) // Premier élément
	{
		current->next->prev = NULL;
		data->varenv_lst = current->next;
	}
	else if (!current->next && current->prev) // Dernier élément
	{
		current->prev->next = NULL;
	}
	else if (current->prev && current->next) // Élément au milieu
	{
		current->next->prev = current->prev;
		current->prev->next = current->next;
	}
	else // Unique élément dans la liste
	{
		data->varenv_lst = NULL;
	}
	free(temp->name);
	free(temp->value);
	free(temp);
}

static bool	ft_remove_var(t_data *data, char *var_name)
{
	t_varenv	*current;

	current = data->varenv_lst;
	while (current)
	{
		if (ft_strcmp(var_name, current->name) == 0)
		{
			ft_unset_utils(current, data);
			return (true);
		}
		current = current->next;
	}
	return (false);
}
int	ft_unset(t_data *data, t_cmd *cmd)//TODO : unset PATH
{
	int		i;
	int		removed;

	if (cmd->argc < 2)
		return (0);
	i = 1;
	removed = 0;
	while (i < cmd->argc)
	{
		if (ft_remove_var(data, cmd->argv[i]))
			removed = 1;
		i++;
	}
	if (removed)
		data->lst_exit = 0;
	else
		data->lst_exit = 1;
	update_exit_status(data->varenv_lst, data->lst_exit);
	return (data->lst_exit);
}


// void        ft_unset_utils(t_varenv *current, t_data *data)
// {
//     t_varenv *temp;

//     temp = current;
//     if (!current->prev && current->next) //first
//     {
//         current->next->prev = temp->prev;
//         data->varenv_lst = current->next;
//     }
//     else if (!current->next && current->prev) //last
//     {
//         current->prev->next = temp->next;
//     }
//     else //other
//     {
//         current->next->prev = temp->prev;
//         current->prev->next = temp->next;
//     }
//     free(temp->name);
//     free(temp->value);
//     temp = NULL;
// }

// static bool	ft_remove_var(t_data *data, char *var_name)
// {
// 	t_varenv	*current;

// 	current = data->varenv_lst;
// 	while (current)
// 	{
// 		if (ft_strcmp(var_name, current->name) == 0)
// 		{
// 			printf("🔍 Suppression de la variable : %s\n", var_name);
// 			ft_unset_utils(current, data);
// 			return (true);
// 		}
// 		current = current->next;
// 	}
// 	printf("❌ Variable non trouvée : %s\n", var_name);
// 	return (false);
// }

// int	ft_unset(t_data *data, t_cmd *cmd)
// {
// 	int	i;

// 	if (cmd->argc < 2)
// 		return (0);
// 	i = 1;
// 	while (i < cmd->argc)
// 	{
// 		ft_remove_var(data, cmd->argv[i]);
// 		i++;
// 	}
// 	// Si PATH est supprimé, tout programme externe devient introuvable
// 	if (!get_env_value(data->varenv_lst, "PATH"))
// 	{
// 		printf("⚠️ Attention : PATH supprimé, les commandes externes ne fonctionneront plus !\n");
// 	}
// 	data->lst_exit = 0;
// 	update_exit_status(data->varenv_lst, data->lst_exit);
// 	return (0);
// }

/*
typedef struct s_cmd
{
	char					*value;
	char					**argv;
	int						argc;
	pid_t					pid;
	t_redirection			*redirection;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_varenv
{
	char					*name;
	char					*value;
	struct s_varenv			*next;
	struct s_varenv			*prev;
	bool					hiden;
}							t_varenv;
                            
typedef struct s_data
{
	t_cmd					*cmd_lst;
	t_varenv				*varenv_lst;
	t_token					*tok_lst;
	int						lst_exit;
	char					**histo;
}							t_data;
*/