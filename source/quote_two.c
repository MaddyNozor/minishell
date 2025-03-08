/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/08 16:12:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

char    *ft_varenv_manager(char *string)
{
    t_list  *stock_list;
    char    *new_content;
    char    *slice;
    int     i;
    
    stock_list = NULL;
    i = 0;
    while (string[i])
    {
        slice = ft_varenv_slicing(string, &i); // Découpe un morceau et avance i
        ft_stock_the_slice(&stock_list, slice); // Ajoute à la liste chaînée
    }
    new_content = ft_glue_the_slices_again(stock_list); // Recompose la string
    ft_lstclear(&stock_list, free); // Nettoie la liste temporaire
    free(string); // Libère l'ancien contenu
    return (new_content);
}

char *ft_varenv_slicing(char *content, int *i)
{
    char *slice;
    
    slice = NULL;
    if (content[*i] == '$')
    {    
        slice = ft_cut_varenv(content, i);
        slice = ft_fake_expand_varenv(slice);
//        slice = ft_expand_varenv(slice, t_varenv *varenv)
    }
    else
        slice = ft_cut_normal_text_but_varenv(content, i);
    if (slice == NULL)
        return (NULL);
    return (slice);
}

char    *ft_cut_varenv(char *content, int *i)
{
    int start;
    char *slice;
    
    start = *i;
    slice = NULL;
    (*i)++; //passe le $
    while(content[*i])
    {
        if (content[*i] == '?' || (content[*i] >= '0' && content[*i] <= '9'))
        {
            (*i)++;
            break;
        }
        else if (content[*i] != '_' && ft_isalpha(content[*i]) == false)
            break;
        else
            while(ft_isalnum(content[*i]) || content[*i] == '_')
                (*i)++;
    }
    slice = ft_substr(content, start, *i - start);
    if (!slice)
        return (NULL);
    return (slice);
}

char *ft_expand_varenv(char *var_found) // t_varenv *varenv
{
    char *prefix = "[VARENV:";
    char *suffix = "]";
    char *temp;
    char *fake_var_env;

    temp = ft_strjoin(prefix, var_found); // "[VARENV:" + var_found
    fake_var_env = ft_strjoin(temp, suffix); // "[VARENV:var_found]"

    free(temp);
    return (fake_var_env);
}

char *ft_cut_normal_text_but_varenv(char *content, int *i)
{
    int start;
    char *slice;
    
    start = *i;
    slice = NULL;
    while (content[*i] && content[*i] != '$')
        (*i)++;
    slice = ft_substr(content, start, *i - start);
    if (slice == NULL)
        return (NULL);
    return (slice);
}


