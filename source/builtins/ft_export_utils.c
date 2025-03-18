/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:34:40 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/18 16:36:48 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

int    found_sign_equal_in_word(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (i);
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
