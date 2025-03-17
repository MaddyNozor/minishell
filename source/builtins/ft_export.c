/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:02:30 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/17 18:41:15 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void        ft_print_list_export(t_data *data)
{
    t_varenv    *current;

    current = data->varenv_lst;
    while (current)
    {
        if (current->name)
        {
            printf("export %s", current->name); 
            if (current->value)
                printf("=\"%s\"", current->value);
            printf("\n");
        }
        current = current->next;
    }
}

int    found_sign_equal_in_word(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
        {
            // printf("%d\n", i);
            return (i);
        }
        i++;
    }
    return (-1);   
}

bool    is_valid_name(char *name)
{
    int i;
    
    if (!name)
        return (false);
    i = 1;
    while (name [i])
    {
        if(!ft_isalnum(name[i]) && name[i] != '_')
            return (false);
        i++;
    }
    return (true);
}

t_varenv *ft_check_if_varenv_exist(t_varenv *list, char *name)
{
    t_varenv *current;

    current = list;
    while (current)
    {
        if (ft_strcmp(current->name, name) == 0 )
            return current;
        current = current->next;
    }
    return (NULL);
}

void       ft_export(t_data *data, t_cmd *cmd)
{
    int         i;
    char        *name;
    char        *value;
    int         split_pos;
    t_varenv    *varenv_exist;

    if (cmd->argc == 1)
    {   
        ft_print_list_export(data);
        return;
    }
    i = 1;
    while (i < cmd->argc)
    {
        name = NULL;
        value = NULL; 
        varenv_exist = NULL;
        split_pos = found_sign_equal_in_word(cmd->argv[i]);
        if (split_pos >= 0)
        {
            name = ft_substr(cmd->argv[i], 0, split_pos);
            value = ft_substr(cmd->argv[i], split_pos + 1, strlen(cmd->argv[i]) - split_pos);
        }
        else
            name = ft_strdup(cmd->argv[i]);
        if (is_valid_name(name) == false)
        {
            printf("export: '%s' : not a valid identifier \n", name);
            free(name);
            if (value)
                free(value);
        }
        else if (name)
            varenv_exist = ft_check_if_varenv_exist(data->varenv_lst, name);
        else if (varenv_exist != NULL)
        {
            if (value)
            {
                free(varenv_exist->value);
                varenv_exist->value = value;
            }
            free(name);
        }
        else if (name != NULL && value != NULL)
            create_varenv(&data->varenv_lst, name, value, false);
        i++;
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
