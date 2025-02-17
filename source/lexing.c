/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/02/17 14:19:08 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/lexing.h"
# include "../include/init_shell.h"

bool    ft_is_whitespace(char c)
{
    if (c == ' ' || (c >= '\t' && c <= '\r'))
        return (true);
    else
        return (false);
}

int ft_stop_the_count(char c)
{
    if (c == '<' || c == '|' || c == '>' || c == '$'
        || ft_is_whitespace(c) == true)
        return true;
    return false;
}

int is_an_operator(int type)
{
    if (type == PIPE 
        || type == REDIRECT_IN || type == REDIRECT_OUT 
        || type == APPEND_OUT || type == HEREDOC)
        return true;
    return false;
}

t_token    *token_type_operators(char *line, int i, t_token *new_token)
{
    if (line[i] == '<')
    {
        if  (line[i + 1] == '<')
            new_token = init_type_token_with_x_char_of_line(
                HEREDOC, new_token, 2, line, i);
        else
            new_token = init_type_token_with_x_char_of_line(
                REDIRECT_IN, new_token, 1, line, i);
    }
    else if (line[i] == '>')
    {
        if  (line[i + 1] == '>')
            new_token = init_type_token_with_x_char_of_line(
                APPEND_OUT, new_token, 2, line, i);
        else
            new_token = init_type_token_with_x_char_of_line(
                REDIRECT_OUT, new_token, 1, line, i);
    }
    else if  (line[i] == '|')
        new_token = init_type_token_with_x_char_of_line(
            PIPE, new_token, 1, line, i);
    if (new_token == NULL)
        return (NULL);
    return (new_token);
}

t_token    *token_type_varenv(char *line, int i, t_token *new_token)
{
    int len_varenv;

    if  (line[i + 1] == '?')
        new_token = init_type_token_with_x_char_of_line(
            LAST_EXIT, new_token, 2, line, i);
    else if ( line[i + 1] >= '0' && line[i + 1] <= '9')
        new_token = init_type_token_with_x_char_of_line(
            VAR_ENV, new_token, 2, line, i);
    else if (line[i + 1] != '_' && ft_isalpha(line[i + 1]) == FALSE)
        new_token = init_type_token_with_x_char_of_line(
            WORD, new_token, 1, line, i);
    else
    {
        len_varenv = 2;
        while (ft_isalnum(line[i + len_varenv]) || line[i + len_varenv] == '_')
            len_varenv++;
        new_token = init_type_token_with_x_char_of_line(
            VAR_ENV, new_token, len_varenv, line, i);
    }
    if (new_token == NULL)
        return (NULL);
    return(new_token);
}

t_token    *token_type_word(char *line, int i, t_token *new_token)
{
    int len;
    int quote_open;
    char    type_of_quote;

    len = 0;
    quote_open = false;
    while (line[i + len] && ft_stop_the_count(line[i + len]) == false) 
    {
        if(line[i + len] == '\'' || line[i + len] == '\"')
        {
            quote_open = true;
            type_of_quote = line[i + len];
            ft_printf("type of quote: %c\n", type_of_quote);
            len++;
            while(line[i + len] && line[i + len] != type_of_quote)
                len++;
            if(!line[i + len])
                return (ft_printf("rajoute une quote !\n"), NULL);
            if(line[i + len] == type_of_quote)
                quote_open = false;
        }
        len++;
    }
    new_token = init_type_token_with_x_char_of_line(
        WORD, new_token, len, line, i);
    if (new_token == NULL) //TODO: QUestion, si l'init fail, new token sera deja == NULL non ? besoin de proteger en dessous quand meme ?
        return (NULL);
    return(new_token);
}

/// tempo pour test
/// @param lst pointeur sur la tete de la liste
void	print_list(t_token *lst)
{
    while (lst)
    {
        printf("Token: %s, Type: %d\n",
               lst->content, lst->type);
        lst = lst->next;
    }
    printf("--List Printed--\n");
}

int check_lexing(t_token *head_of_list)
{
    t_token *current_token;
    
    if (head_of_list == NULL)
        return SUCCESS;
    else if (head_of_list->type == PIPE)
        return(FAILURE);  
    current_token = head_of_list;
    while (current_token->next != NULL)
    {
        if (is_an_operator(current_token->type) == true)
            if (is_an_operator(current_token->next->type) == true)
                return (FAILURE);
        current_token = current_token->next;
    }
    return(SUCCESS);
}

t_token  *lexer(char *line)
{
    int i;
    t_token *head_of_list;
    t_token *new_token;
    
    i = 0;
    new_token = NULL;
    head_of_list = NULL;
    while(line[i])
    {
        if (ft_is_whitespace(line[i]) == true)
             i++;
        else 
        {
            if (line[i] == '<' || line[i] == '>' || line[i] == '|')
                new_token = token_type_operators(line, i, new_token);
            else if (line[i] == '$')
                new_token = token_type_varenv(line, i, new_token);
            else
                new_token = token_type_word(line, i, new_token);
            ft_tokadd_back(&head_of_list, new_token);
            i = i + ft_strlen(new_token->content);
        }
    }
    print_list(head_of_list);
    if (check_lexing(head_of_list) == FAILURE)
    {
        head_of_list = NULL;
        ft_printf("Syntax error \n----------------------------------\n");
    }        
    return(head_of_list);
}
