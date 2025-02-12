/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/02/12 17:35:27 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/lexing.h"
# include "../include/init_shell.h"

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


// t_token *init_type_token_with_x_char_of_line(
//     int type, t_token *token, int x, char *line, int i)

// t_token *token_type_greater_than(char *line, int i, t_token *new_token)
// {
//     if  (line[i+1] == '>')
//         new_token=init_type_token_with_x_char_of_line(
//             APPEND_OUT, new_token, 2, line, i);
//     else
//         new_token=init_type_token_with_x_char_of_line(
//             REDIRECT_OUT, new_token, 1, line, i);
//     return(new_token);
// }

// t_token *token_type_less_than(char *line, int i, t_token *new_token)
// {
//     if  (line[i+1] == '<')
//         new_token=init_type_token_with_x_char_of_line(
//             HEREDOC, new_token, 2, line, i);
//     else
//         new_token=init_type_token_with_x_char_of_line(
//             REDIRECT_IN, new_token, 1, line, i);
//     return(new_token);
// }


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

// t_token    *token_type_varenv(char *line, int i, t_token *new_token)
// {
//     int len = 1; // Par défaut, capture juste "$"
//     int type = WORD; // Par défaut, on considère que c'est un mot

//     if (line[i + 1] == '?')
//     {
//         len = 2;
//         type = LAST_EXIT;
//     }
//     else if (line[i + 1] == '_' || ft_isalpha(line[i + 1]) == TRUE)
//     {
//         len = 2;
//         type = VAR_ENV;
//         while (ft_isalnum(line[i + len]) || line[i + len] == '_')
//             len++; // Capture toute la variable d'environnement
//     }

//     new_token = init_type_token_with_x_char_of_line(type, new_token, len, line, i);
//     return (new_token);
// }

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

    len = 1;
    while (line[i + len] != '<' && line[i + len] != '|' 
        && line[i + len] != '>' && ft_is_whitespace(line[i]) == true 
        && line[i + len] != '$')
        len++;
    new_token = init_type_token_with_x_char_of_line(
        WORD, new_token, len, line, i);
    if (new_token == NULL)
        return (NULL);
    return(new_token);
}

/// tempo pour test
/// @param lst pointeur sur la tete de la liste
void	print_list(t_token *lst)
{
    while (lst)
    {
        printf("Token: %s, Type: %d, Prev: %p, Actual %p, Next: %p\n",
               lst->content, lst->type, lst->prev, lst, lst->next);
        lst = lst->next;
    }
    printf("----\n");
}

// int check_lexing(t_token *head_of_list)
// {
//     t_token *current_token;
    
//     if (head_of_list->type == PIPE)
//         return(FAILURE);  
//     current_token = head_of_list;
//     while (current_token->next != NULL)
//     {
//         if token->type == OPERATOR
//             if token+1->type == OPERATOR
//                 return (FAILURE);
//         current->token = current_token->next;
//     }
//     return(SUCCESS);
// }

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
            print_list(head_of_list);
            i = i + ft_strlen(new_token->content);
        }
    }
    if (check_lexing(head_of_list) == FAILURE)
    {
        head_of_list = NULL;        
    }
    return(head_of_list);
}
