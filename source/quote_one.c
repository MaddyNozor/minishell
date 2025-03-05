/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/05 11:16:17 by codespace        ###   ########.fr       */
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

/*
t_token	*token_type_varenv(char *line, int i, t_token *new_token)
{
	int	len_varenv;

	if (line[i + 1] == '?')
		new_token = init_type_token_with_x_char_of_line(LAST_EXIT, 2,
				line, i);
	else if (line[i + 1] >= '0' && line[i + 1] <= '9')
		new_token = init_type_token_with_x_char_of_line(VAR_ENV, 2,
				line, i);
	else if (line[i + 1] != '_' && ft_isalpha(line[i + 1]) == FALSE)
		new_token = init_type_token_with_x_char_of_line(WORD, 1,
				line, i);
	else
	{
		len_varenv = 2;
		while (ft_isalnum(line[i + len_varenv]) || line[i + len_varenv] == '_')
			len_varenv++;
		new_token = init_type_token_with_x_char_of_line(VAR_ENV,
				len_varenv, line, i);
	}
	if (new_token == NULL)
		return (NULL);
	return (new_token);
}
*/

char *ft_expand_var(char *var_found, t_varenv *varenv)
{
    char *prefix = "[VARENV:";
    char *suffix = "]";
    char *temp;
    char *fake_var_env;

    (void)varenv; // On ignore pour l'instant la vraie expansion

    temp = ft_strjoin(prefix, var_found); // "[VARENV:" + var_found
    fake_var_env = ft_strjoin(temp, suffix); // "[VARENV:var_found]"

    free(temp);
    return (fake_var_env);
}

char *ft_find_and_expand_var(char *str, int *i, t_varenv *varenv)
{
    int     start;
    int     len_var;
    char    *var_found;
    char    *expanded_value;

    start = *i;
    len_var = 1; // On commence à 1 car '$' est déjà inclus
    if (str[start + 1] == '?' || ft_isdigit(str[start + 1]) == true)
        len_var = 2;
    else if (str[start + 1] == '_' || ft_isalpha(str[start + 1]))
    {
        len_var++;
        while (ft_isalnum(str[start + len_var]) || str[start + len_var] == '_')
            len_var++;
    }
    var_found = ft_substr(str, start, len_var); // inclu le $ c'est important pour moi
    if (!var_found)
        return (NULL);
    expanded_value = ft_expand_var(var_found, varenv); // Trouve la valeur de la variable - fake pour l'instant
    free(var_found);
    *i += len_var; 
    return (expanded_value); 
}

char *ft_search_var_to_expand_then_trim(char *slice)
{
    t_list *dbl_qt_lst;
    char *subslice;
    char *expanded;
    int i;
    t_varenv *fake_varenv;
    
    fake_varenv = NULL;
    dbl_qt_lst = NULL;
    i = 0;
    while (slice[i])
    {
        if (slice[i] == '$')
            subslice = ft_find_and_expand_var(slice, &i, fake_varenv);
        else
            subslice = ft_cut_normal_text(slice, &i, '"');
        if (subslice == NULL)
            return (NULL);
        ft_stock_the_slice(&dbl_qt_lst, subslice);
    }
    expanded = ft_glue_the_slices_again(dbl_qt_lst);
    if (expanded == NULL)
        return (NULL);
    ft_lstclear(&dbl_qt_lst, free); //on masque ca pour l'instant car double free
    free(slice);
    return (expanded);
}

char *ft_cut_normal_text(char *content, int *i, char type_of_quote)
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
}

char *ft_cut_quoted_text(char *content, int *i)
{
    char quote; //endeux lignes plizzz
    int start;
    char *slice;
    
    quote = content[*i];
    start = *i;
    (*i)++;
    while (content[*i] && content[*i] != quote)
        (*i)++;
    slice = ft_substr(content, start, *i - start + 1); // pk mon start +1 la si je veux d'abord avoir mon fragments a quote ?
    ft_printf("slice cut quote : %s \n", slice);
    if (!slice)
        return (NULL);
    if (quote == '\'')
       slice = ft_trim_quote(slice, quote); // Trim pour les '' peut-être que ft_subtrim suffit 
    else
        slice = ft_search_var_to_expand_then_trim(slice); // Expansion pour les ""
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

t_list *ft_slice_and_stock_content(char *content)
{
    int i;
    char *slice;
    t_list *stock_list;
    t_list *new_node;

    i = 0;
    slice = NULL;
    stock_list = NULL;
    new_node = NULL;
    while(content[i])
    {
        slice = ft_cut_a_slice(content, i);
        if (slice == NULL)
        {
            //free stock of slice if ther is something inside
            return (NULL);
        }
        i += ft_strlen(slice);
        new_node = ft_lstnew(slice);
        ft_lstadd_back(&stock_list, new_node);
    }
    return (stock_list);
}

char *ft_glue_the_slices_again(t_list *list_slice)
{
    char *new_content;
    t_list *current_slice;

    new_content = NULL;
    current_slice = list_slice;
    while (list_slice != NULL)
    {
        new_content = ft_strjoin(current_slice->content, 
            current_slice->next->content);
        if (new_content == NULL)
            return (NULL);
        current_slice = current_slice->next;
    } 
    free(current_slice);
    return(new_content);  
}


avancer juqu'a trouver une quote
copie de l'eventuelle parti avant la quote
copie de la partie entre les deux quotes simples
    SI DOUBLES QUOTES
    avancer dans la quote a la recherche d'un $
    copie de la partie avant dans une boite tempo
    identification de la varenv
    expand var env, stockage resultat dans une boite tempo
    recommencer
    fusionner tous les morceaux ensemble puis liberer les boites tempo
    (= full string expand avec des " de part et d'autre)
trim de la partie entre quotes
reprendre la boucle a partir de la position de l'ancienne quote
lorsque bout du content, fusionner tous les morceaux ensemble dans le bon ordre.
free les blocs qui stochqient temporqirement les morceaux
return le nouveau content


char *ft_cut_a_slice(char *content, int *i)
{
    char *slice;
    int start;
    char quote;

    start = *i;
    if (content[*i] && content[*i] != '\'' && content[*i] != '"')
    {
        while (content[*i] && content[*i] != '\'' && content[*i] != '"')
            (*i)++;
        return (ft_substr(content, start, *i - start)); // Retourne la partie hors-quotes
    }
    quote = content[*i]; // Détecte si c'est ' ou "
    (*i)++; // Passe la quote ouvrante
    start = *i;
    while (content[*i] && content[*i] != quote)
        (*i)++;
    slice = ft_substr(content, start, *i - start);
    if (!slice)
        return (NULL);
    slice = ft_trim_quote(slice, quote); // Supprime la quote ouvrante et fermante
    if (content[*i] == quote)
        (*i)++; // Passe la quote fermante
    return (slice);
}
*/