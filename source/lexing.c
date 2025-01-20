/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/01/20 19:42:03 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/lexing.h"

// # define REDIRECT_OUT 1
// # define APPEND_OUT 2
// # define REDIRECT_IN 3
// # define HEREDOC 4

t_token    *ft_chevron(char *line, int i)
{
    t_token *new;
    
    new = malloc(sizeof(t_token));
    if (new == NULL)
        return (NULL);
    ft_bzero(new, sizeof(t_token));
    // content = NULL;
    if (line[i] == '>')
    {
        if  (line[i+1] == '>')
            // content = ">>";
            ft_tok_new(">>", APPEND_OUT);
        else
            // content = ">";
            ft_tok_new(">", REDIRECT_OUT);
    }
    if (line[i] == '<')
    {
        if  (line[i+1] == '<')
            // content = "<<";
            ft_tok_new("<<", HEREDOC);
        else
            // content = "<";
            ft_tok_new("<", REDIRECT_IN);
    }
    return(new);
}

t_token  *ft_lexing(t_token *lst_token, char *line)
{
    int i;
    t_token *new;
    
    i = 0;
    new = NULL;
    while(line[i])
    {
        if (line[i] == '<' || line[i] == '<')
            new = ft_chevron(line, i);
        // if (line[i] == '|')
        //     content = ft_pipe(line, i);
        // if (ft_is_whitespace(line[i]) == true)
        //     content = ft_whitespace(line, i);
        // if (line[i] == '$')
        //     content = ft_varenv(line, i);
        // while(ft_isprintable(line[i]) == true)
        //     content = ft_word(line, i);
        i++;
    }
    ft_tokadd_back(&lst_token, new);
    return(lst_token);
}
