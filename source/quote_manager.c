/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/02/26 16:37:40 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

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

char *ft_expand_and_trim(char *slice)
{
    (void)slice;
    return(NULL);
}


char *ft_cut_normal_text(char *content, int *i)
{
    int start = *i;
    
    while (content[*i] && content[*i] != '\'' && content[*i] != '"')
        (*i)++;
    return (ft_substr(content, start, *i - start));
}

char *ft_cut_quoted_text(char *content, int *i)
{
    char quote = content[*i];
    int start;
    
    start = *i;
    (*i)++;
    while (content[*i] && content[*i] != quote)
        (*i)++;
    char *slice = ft_substr(content, start + 1, *i - start);
    if (!slice)
        return (NULL);
    if (quote == '"')
        slice = ft_expand_and_trim(slice); // Expansion pour les ""
    else
        slice = ft_trim_quote(slice, quote); // Trim pour les ''
    if (content[*i] == quote)
        (*i)++; // Passe la quote fermante
    return (slice);
}

char *ft_cut_a_slice(char *content, int *i)
{
    char *slice;

    slice = NULL;
    if (content[*i] == '\'' || content[*i] == '"')
        slice = ft_cut_quoted_text(content, i); // Gère les quotes
    else
        slice = ft_cut_normal_text(content, i); // Gère le texte normal
    if (slice == NULL)
        return (NULL);
    return (slice);
}

void ft_stock_the_slice(t_list **stock_list, char *slice)
{
    t_list *new_node;

    if (!slice || !*slice) // Vérifie que le slice n'est pas NULL ou vide
    {
        free(slice);
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
        return (ft_strdup("")); // Évite un NULL

    new_content = ft_strdup("");
    if (!new_content)
        return (NULL);
    
    current = list_slice;
    while (current)
    {
        temp = ft_strjoin(new_content, current->content);
        free(new_content);
        new_content = temp;
        if (!new_content)
            return (NULL); // Sécurise contre un échec d'allocation
        current = current->next;
    }
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


/*char    *ft_quote_manager(char *actual_content)
{
    char    *new_content;
    int     i;

    i = 0;
    while (actual_content[i])
    {
		if (actual_content[i] == '\'') 
        {
            new_content = ft_trim_quote(actual_content, '\'');
        }
        else if(actual_content[i] == '\"') 
        {
            ft_printf("double quote on gere ca plus tard\n");
            new_content = actual_content;
        }
        i++;
    }
    ft_printf("after trim %s \n", new_content);
    free(actual_content);
    return(new_content);
}*/

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
