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


//peut etre qu'ici utiliser ft_trim tout court pourrait marcher comme on aura
//jamais plus d'une quote de chaque cote en fermeture
//'dfdf' =1 'dfg''=invalid ''dfg''=2 paires 'd'f'g'=2paires
// '""'=1 'sdkjfhksdfdsf"""""""""""""'=1 'sdkjfhksdfdsf" ' """"""'=invalid (3')

char	*ft_trim_quote(char const *s1, char const q)//ca c'est pour les quotes simples, prevoir version quotes simples et doubles
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

/*
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
*/


char    *ft_quote_manager(char *actual_content)
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
                cur_token->content = ft_quote_manager(cur_token->content);
        }
		cur_token = cur_token->next;
	}
    return(head_of_list);
}
