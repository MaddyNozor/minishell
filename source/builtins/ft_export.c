/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:02:30 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/18 16:08:18 by mairivie         ###   ########.fr       */
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

int ft_split_name_and_value(char **name, char **value, char *str_to_split)
{
    int         split_pos;
    
    split_pos = found_sign_equal_in_word(str_to_split);
    if (split_pos >= 0)
    {
        *name = ft_substr(str_to_split, 0, split_pos);
        if(*name == NULL)
            return (FAILURE); //code erreur malloc
        *value = ft_substr(str_to_split, split_pos + 1, 
            ft_strlen(str_to_split) - split_pos);
        if(*value == NULL)
            return (FAILURE); //code erreur malloc
            //FAUX, y avait peut etre juste pas de value !!!
    }
    else
    {   
        *name = ft_strdup(str_to_split);
        if(*name == NULL)
            return (FAILURE); //code erreur malloc
    }
    return (SUCCESS);
}
void    free_name_value_if_invalid(char **name, char **value)
{
    if (*name)
    {
        printf("export: '%s' : not a valid identifier \n", *name);
        free(*name);
    }
    else if (*value)
        free(*value);
    return;
}
int    ft_replace_varenv_value(char **name, char **value, t_varenv *varenv)
{
    if (*value)
    {
        free(varenv->value);
        varenv->value = *value;
    }
    free(*name);
    return (SUCCESS);
}

void    ft_create_exported_varenv(char **name, char **value, t_varenv *list)
{
    t_varenv    *already_exist;

    already_exist = NULL;
    if (*value == NULL)
    {
        free(*name);
        return;   
    }
    if (*name)
        already_exist = ft_check_if_varenv_exist(list, *name);
    if (already_exist != NULL)
        ft_replace_varenv_value(name, value, already_exist);
    else if (*name != NULL && *value != NULL)
        create_varenv(&list, *name, *value, false);
}

int       ft_export(t_data *data, t_cmd *cmd)
{
    int         i;
    char        *name;
    char        *value;

    if (cmd->argc == 1)
        return (ft_print_list_export(data), SUCCESS);
    i = 1;
    while (i < cmd->argc)
    {
        name = NULL;
        value = NULL; 
        if (ft_split_name_and_value(&name, &value, cmd->argv[i]) == false)
            return (FAILURE); // code erreur malloc a fail
        if (is_valid_name(name) == false)
            return (free_name_value_if_invalid (&name, &value), FAILURE); //failure = code erreur not a valid ID
        ft_create_exported_varenv(&name, &value, data->varenv_lst);
        i++;
    }
    return(SUCCESS);
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
