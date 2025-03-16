/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:02:30 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/16 14:28:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void       ft_export(t_data *data, t_cmd *cmd)
{
    //int i;
    t_varenv    *current;

    //i = 1;
    if (cmd->argc == 1)
    {
        current = data->varenv_lst;
        while (current)
        {
            if (current->name)
            {
                printf("export : %s", current->name); 
                if (current->value)
                    printf("=%s", current->value);
                printf("\n");
            }
            current = current->next;
        }
    }
}

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
        
/*
Si absence d'arguments : 
comme env tot court mais avec export devant chaque var env

Analyse argument :
- si char bloquant
    => error export
- sinon si signe = dans le token == true
    => ft_export_equal
- sinon
    => ft_export_like_this

ft_export_equal (string)
Split autour du premier egal :
    - before = NAME
    - after = value
if NAME existe deja (=comparaison avec tous les names des tokens varenv existant deja)
On prend le token var-env et on remplace la ligne value (free ancienne valeur)
free l'argument complet comme on le split
Si NAME existe deja, free name_arg
free l'ancienne value

SI name n'existe pas encore
creation nouveau token var env + ajout back list chainee
free l'arg (car on garde que le copie des parties Name et value)

ft_export_like_this
new token var env avec 
value = NULL
NAME = copie de string_arg
free argument 

ajout en fin de liste chainee
*/
