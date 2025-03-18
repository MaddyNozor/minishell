/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:02:30 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/18 16:39:27 by mairivie         ###   ########.fr       */
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

