/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:50:26 by mairivie          #+#    #+#             */
/*   Updated: 2025/01/23 14:54:39 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

//--------------------- INCLUDES -----------------------------
# include "../libft/libft.h" // libft mairivie
# include <unistd.h> //
# include <stdlib.h> //
# include <stdbool.h> // type bool
# include <stdio.h> // printf pour les tests

//--------------------- DEFINES -----------------------------
# define FAILURE 1
# define SUCCESS 0 

//--TOKEN_TYPE
# define BLANK 0
# define REDIRECT_OUT 1
# define APPEND_OUT 2
# define REDIRECT_IN 3
# define HEREDOC 4
# define PIPE 5
# define VAR_ENV 6
# define WORD 7
# define SIMPLE_Q 8
# define DOUBLE_Q 9

//--------------------- STRUCTURES -----------------------------

typedef struct s_redirection
{
        char                    *file_name;
        int                     type;
        struct s_redirection    *next;
} t_redirection;

typedef struct s_cmd
{
        char            *value;
        char            **argv;
        int             argc;
        pid_t           pid;
        t_redirection   *redirection;
        struct s_cmd    *next;
} t_cmd;

typedef struct s_varenv {
        char            *name;                                    
        char            *value;                                           
        struct s_varenv *next;
        struct s_varenv *prev;
        bool            hiden;
} t_varenv;

typedef struct s_protoken {                                  
        char            *content;                                           
        int             type;
} t_protoken;  

typedef struct s_token {                                  
        char            *content;                                           
        struct s_token  *next;
        struct s_token  *prev;
        int             type;
} t_token;                                        

typedef struct s_data {                                  
        t_cmd           *cmd_lst;                                          
        t_varenv        *varenv_lst;
        t_token         *tok_lst;
        int             lst_exit;
        char            **histo;
} t_data;  

//--------------------- FONCTION -----------------------------

t_token	*ft_tok_new(void *content, int type);
t_token	*ft_toklast(t_token *lst);
void	ft_tokadd_back(t_token **lst, t_token *new);
// t_token	*ft_token_new(void *content, int type);
t_token *ft_lexing(t_token *tok_lst, char *line);
t_token *ft_chevron(char *line, int i, t_token *new_token);
bool    ft_is_whitespace(char c);

#endif