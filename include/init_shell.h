/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:50:26 by mairivie          #+#    #+#             */
/*   Updated: 2025/01/24 13:09:47 by sabellil         ###   ########.fr       */
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
# define FAILURE 1
# define SUCCESS 0 

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
void    free_token_list(t_token *list);
// t_token *lexer(char *input);
// t_cmd   *parser(t_token *tok);
// void	executer(t_data *data, char **envp);

// //EXECUTER
// void	executer(t_data *data, char **envp);
// void	executer_simple_cmd(t_cmd *cmd, t_data *data, char **envp);
// bool	is_builtin(const char *cmd_value);
#endif