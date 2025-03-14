/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:02:30 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/14 18:28:59 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void       ft_unset(t_data *data, t_cmd *cmd)
{
    int i;
    t_varenv *current;
    t_varenv *temp;

    i = 1;
    // current = data->varenv_lst;
    if (cmd->argc < 1)
        return;
    while (i < cmd->argc)
    {
        temp = NULL;
        printf("4\n");
        current = data->varenv_lst;
        while (current)
        {
            printf("Z\n");
            if (ft_strcmp(cmd->argv[i], current->name) == 0)
            {
                temp = current;
                if (!current->prev && current->next) //first
                {
                    current->next->prev = temp->prev;
                    data->varenv_lst = current->next;
                    //free(current);
                    printf("next\n");
                }
                else if (!current->next && current->prev) //last
                {
                    current->prev->next = temp->next;
                    //free(current);
                    printf("prev\n");
                }
                else //other
                {
                    current->next->prev = temp->prev;
                    printf("prev = prev\n");
                    current->prev->next = temp->next;
                    printf("next = next\n");
                }
                printf("5\n");
                free(temp->name);
                printf("6\n");
                free(temp->value);
                
            }
            current = current->next;
        }
        printf("8\n");
        i++;
    }
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