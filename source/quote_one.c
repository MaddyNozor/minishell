/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/06 11:17:50 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

/*
char *ft_cut_a_slice(char *content, int *i)
{
    char *slice;
    
    slice = NULL;
    if (content[*i] == '\'' || content[*i] == '"')
        slice = ft_cut_quoted_text(content, i);
    else
        slice = ft_cut_normal_text(content, i);
    if (slice == NULL)
        return (NULL);
    return (slice);
}
*/

//Vire uniquement les quotes en debut et fin de token. 
//Pour les token multiquotes c'est pqs qdqpté.
char	*ft_trim_quote(char const *s1, char const q)//pour quotes simples, prevoir doubles
{
    size_t	start;
    size_t	end;
    size_t	i;
    char	*new_s;

    if (s1 == NULL || !q)
        return (NULL);
    start = 0;
    if (s1[start] && s1[start] == q)
        start++;
    end = ft_strlen (s1);
    if (s1[end - 1] == q)
        end--;
    new_s = malloc (((end - start) + 1) * sizeof(char));
    if (new_s == 0)
        return (0);
    i = 0;
    while (end > (start + i))
    {
        new_s[i] = s1[start + i];
        i++;
    }
    new_s[i] = '\0';
    return (new_s);
}

char *ft_expand_and_trim(char *slice)
{
    (void)slice;
    return(NULL);
    
/*    t_list *dbl_qt_lst;
    char *expanded;
    int i;
    
    dbl_qt_lst = NULL;
    i = 0;
    while (slice[i])
    {
        if (slice[i] == '$')
        slice = ft_expand_var(slice, &i);
        else
        slice = ft_cut_normal_text(slice, &i);
        if (slice == NULL)
        return (NULL);
        ft_stock_the_slice(&dbl_qt_lst, slice);
    }
    expanded = ft_glue_the_slices_again(dbl_qt_lst);
    if (expanded == NULL)
    return (NULL);
    ft_lstclear(&dbl_qt_lst, free);
    free(slice);
    return (expanded);*/
}

char *ft_cut_normal_text(char *content, int *i, char quote_type)
{
    int start;
    char *slice;
    
    start = *i;
    slice = NULL;
    ft_printf("normal text \n");
    if (quote_type == BLANK)
    {
        ft_printf("blank quote \n");
        while (content[*i] && content[*i] != '\'' && content[*i] != '"')
            (*i)++;
    }
    else
    {
        ft_printf("quote : %c \n", quote_type);
        while (content[*i] && content[*i] != quote_type)
            (*i)++;
    }
    slice = ft_substr(content, start, *i - start);
    if (slice == NULL)
        return (NULL);
    return (slice);
}

/*char *ft_cut_normal_text(char *content, int *i, char type_of_quote)
{
    int start;
    char *slice;
    
    start = *i;
    slice = NULL;
    while (content[*i] && content[*i] != type_of_quote)
        (*i)++;
    slice = ft_substr(content, start, *i - start);
    if (slice == NULL)
        return (NULL);
    return (slice);
}*/

char *ft_cut_quoted_text(char *content, int *i)
{
    char quote;
    int start;
    
    quote = content[*i];
    start = *i;
    ft_printf("quoted text %c \n", quote);
    (*i)++;
    while (content[*i] && content[*i] != quote)
        (*i)++;
    char *slice = ft_substr(content, start + 1, *i - start);
    if (!slice)
        return (NULL);
//    if (quote == '\'')
       slice = ft_trim_quote(slice, quote); // Trim pour les '' peut-être que ft_subtrim suffit 
//    else
//        slice = ft_expand_and_trim(slice); // Expansion pour les ""
//    if (content[*i] == quote)
//        (*i)++; // Passe la quote fermante 
    return (slice);
}

/*
char *ft_cut_a_slice(char *content, int i)
{
    char *slice;
    int start;
    //type_of_quote
    
    slice = NULL;
    start = i;
    while(content[i] != '\'')// une des deux quotes
        i++;
    //type_of_quote = content[i]
    if (i - start != 0)
    {
        slice = ft_substr(content, start, i);
        return (slice);
    }
    while(content[i] != '\'') // type of quote
        i++;
    slice = ft_substr(content, start, (i - start));
    slice = ft_trim_quote(slice, '\''); //peut-etre type of quote directement ?
    return (slice);
}
*/