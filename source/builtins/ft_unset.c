/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:02:30 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/19 15:26:00 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void        ft_unset_utils(t_varenv *current, t_data *data)
{
    t_varenv *temp;

    temp = current;
    if (!current->prev && current->next) //first
    {
        current->next->prev = temp->prev;
        data->varenv_lst = current->next;
    }
    else if (!current->next && current->prev) //last
    {
        current->prev->next = temp->next;
    }
    else //other
    {
        current->next->prev = temp->prev;
        current->prev->next = temp->next;
    }
    free(temp->name);
    free(temp->value);
    temp = NULL;
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

int	ft_unset(t_data *data, t_cmd *cmd)
{
	int	i;
	int	error_flag;

	if (cmd->argc < 2)
		return (0);
	i = 1;
	error_flag = 0;
	while (i < cmd->argc)
	{
		if (!ft_remove_var(data, cmd->argv[i]))
		{
			printf("bash: unset: `%s': not found\n", cmd->argv[i]);
			error_flag = 1;
		}
		i++;
	}
	data->lst_exit = error_flag;
	update_exit_status(data->varenv_lst, data->lst_exit);
	return (error_flag);
}

/*
Si absence d'arg > return
tant qu'il reste des arguments a check
- comparer arg avec varenv->NAME
    si it's a match
     temp = copie de l'adresse de l'arg en question
     pop the arg (previous = next->previous // next = previous->next)
     free tout les champs de la varenv dans timespecreset temp a NULL;
- arg ++

*/
     
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