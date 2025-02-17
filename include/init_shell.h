/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:50:26 by mairivie          #+#    #+#             */
/*   Updated: 2025/02/17 11:05:32 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_SHELL_H
# define INIT_SHELL_H

//--------------------- INCLUDES -----------------------------
# include "../libft/libft.h" // libft mairivie
# include <unistd.h> //
# include <stdlib.h> //
# include <stdio.h> // printf pour les tests
# include <stdbool.h>//++
#include <readline/readline.h>
#include <readline/history.h>

//--------------------- DEFINES -----------------------------
# define FAILURE 0
# define FALSE 0
# define SUCCESS 1 
# define TRUE 1

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
# define LAST_EXIT 10



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

//SHELL INITIALIZATION
t_varenv    *init_varenv(char **envp);
void    init_minimalist_env(t_varenv **varenv_lst);
void    init_existing_env(t_varenv **varenv_lst, char **envp);
void    create_varenv(t_varenv **varenv_lst, char *name, char *value, bool hiden);


//READLINE MAIN LOOP
void    ft_start_minishell(t_data *data, char **envp);
void    free_token_list(t_token **list);
t_token *lexer(char *input);
// t_cmd   *parser(t_token *tok);
// void	executer(t_data *data, char **envp);

t_token	*ft_tok_new(void *content, int type);
t_token	*ft_toklast(t_token *lst);
void	ft_tokadd_back(t_token **lst, t_token *new);
t_token *init_type_token_with_x_char_of_line(
    int type, t_token *token, int x, char *line, int i);
// t_token	*ft_token_new(void *content, int type);
t_token  *lexer(char *line);
t_token *ft_chevron(char *line, int i, t_token *new_token);
bool    ft_is_whitespace(char c);

// //EXECUTER
// void	executer(t_data *data, char **envp);
// void	executer_simple_cmd(t_cmd *cmd, t_data *data, char **envp);
// bool	is_builtin(const char *cmd_value);
#endif