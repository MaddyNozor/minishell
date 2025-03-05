/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/05 11:19:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

/* ************************************************************************** */
/* This file contains functions for handling quoted strings.                 */
/* WARNING: Input strings must have valid quotes!                            */
/* - Every opening quote must have a corresponding closing quote.            */
/* - Unclosed or invalid quotes must be filtered OUT BEFORE calling these.   */
/* - Do NOT pass unverified strings to these functions.                      */
/* Any changes to the parsing logic must ensure this condition is met.       */
/* ************************************************************************** */

char *ft_cut_a_slice(char *content, int *i)
{
    char *slice;
    char type_of_quote;
    
    slice = NULL;
    type_of_quote = BLANK;
    if (content[*i] == '\'' || content[*i] == '"')
    {
        ft_printf("cut a slice quoted \n");
        type_of_quote = content[*i];
        slice = ft_cut_quoted_text(content, i);
    }
    else
    {
        ft_printf("cut a slice normal \n");
        slice = ft_cut_normal_text(content, i, type_of_quote);
    }
    if (slice == NULL)
        return (NULL);
    return (slice);
}

void ft_stock_the_slice(t_list **stock_list, char *slice)
{
    t_list *new_node;
    
    if (!slice || !*slice) // Vérifie que le slice n'est pas NULL ou vide
    {
        free(slice); //free stock list non, comme ca veut dire que malloc a echoue pour la slice non ?
        return;
    }
    new_node = ft_lstnew(slice);
    if (!new_node)
    {
        free(slice);
        return;
    }
    ft_lstadd_back(stock_list, new_node);
}

char *ft_glue_the_slices_again(t_list *list_slice)
{
    char *new_content;
    char *temp;
    t_list *current;

    if (!list_slice)
        return (ft_strdup("")); // Évite un NULL. ??????? WHY ???
    new_content = ft_strdup("");
    if (!new_content)
        return (NULL);
    temp = NULL;
    current = list_slice;
    while (current)
    {
        temp = ft_strjoin(new_content, current->content);
        if (temp == NULL)
            return (NULL); // Sécurise contre un échec d'allocation
        new_content = temp;
//      free(temp ?????);
        current = current->next;
    }
    //free toute la list_slice d'ailleurs on en a plus besoin je crois
    return (new_content);
}

char    *ft_quote_manager(char *actual_content)
{
    t_list  *stock_list;
    char    *new_content;
    char    *slice;
    int     i;

    stock_list = NULL;
    i = 0;
    while (actual_content[i])
    {
        slice = ft_cut_a_slice(actual_content, &i); // Découpe un morceau et avance i
        ft_stock_the_slice(&stock_list, slice); // Ajoute à la liste chaînée
    }
    new_content = ft_glue_the_slices_again(stock_list); // Recompose la string
    ft_lstclear(&stock_list, free); // Nettoie la liste temporaire

    free(actual_content); // Libère l'ancien contenu
    return (new_content);
}

t_token *ft_spot_the_quotes(t_data *data)
{
    t_token *cur_token;
    t_token *head_of_list;

    cur_token = data->tok_lst;
    head_of_list = data->tok_lst;
    while (cur_token != NULL)
	{
		if (cur_token->type == WORD)
        {
            if(cur_token->nb_quote > 0)
            {
                ft_printf("before: %s \n", cur_token->content);
                cur_token->content = ft_quote_manager(cur_token->content);
                ft_printf("after: %s \n", cur_token->content);
            }
        }
		cur_token = cur_token->next;
	}
    return(head_of_list);
}
