/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/01/23 15:09:10 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/lexing.h"

// # define REDIRECT_OUT 1
// # define APPEND_OUT 2
// # define REDIRECT_IN 3
// # define HEREDOC 4

bool    ft_is_whitespace(char c)
{
    if (c == ' ' || (c >= '\t' && c <= '\r'))
        return (true);
    else
        return (false);
}
t_token    *ft_chevron(char *line, int i, t_token *new_token)
{
    if (line[i] == '>')
    {
        if  (line[i+1] == '>')
            new_token=ft_tok_new(">>", APPEND_OUT);
        else
            new_token=ft_tok_new(">", REDIRECT_OUT);
    }
    if (line[i] == '<')
    {
        if  (line[i+1] == '<')
            new_token=ft_tok_new("<<", HEREDOC);
        else
            new_token=ft_tok_new("<", REDIRECT_IN);
    }
    if  (line[i] == '|')
        new_token=ft_tok_new("|", PIPE);
    return(new_token);
}


t_token  *ft_lexing(t_token *tok_lst, char *line)
{
    int i;
    t_token *new;
    
    i = 0;
    new = NULL;
    while(line[i])
    {
        if (ft_is_whitespace(line[i]) == true)
             i++;
        else 
        {
            if (line[i] == '<' || line[i] == '>' || line[i] == '|')
                new = ft_chevron(line, i, new);
            // if (line[i] == '$')
            //     new = ft_varenv(line, i);
                // while(ft_isprintable(line[i]) == true)
                //     content = ft_word(line, i);
            // printf("content = %s, type : %d, prev : %p, next : %p  \n", new->content, new->type, new->next, new->prev);
            ft_tokadd_back(&tok_lst, new);
            printf("content = %s, type : %d, prev : %p, next : %p  \n", new->content, new->type, new->next, new->prev);
            i = i + ft_strlen(new->content);
            //new->prev = new;
            new = new->next;
        }
    }
            free(new);
    return(tok_lst);
}
