/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:50:26 by mairivie          #+#    #+#             */
/*   Updated: 2025/02/21 15:57:18 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_SHELL_H
# define INIT_SHELL_H

//--------------------- INCLUDES -----------------------------
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>

//--------------------- DEFINES -----------------------------
# define FAILURE_L 0 //TODO: traque des success et failure dans le lexing
# define FALSE 0
# define SUCCESS_L 1
# define TRUE 1

# define FAILURE 1
# define SUCCESS 0
# define REDIR_IN 1
# define REDIR_OUT 2
# define REDIR_APPEND 3
# define REDIR_HEREDOC 4

//--TOKEN_TYPE_LEXING
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

// //--TOKEN_TYPE_LEXING
// # define BLANK 0
// # define REDIRECT_OUT 1
// # define APPEND_OUT 2
// # define REDIRECT_IN 3
// # define HEREDOC 4
// # define PIPE 5
// # define VAR_ENV 6
// # define WORD 7
// # define SIMPLE_Q 8
// # define DOUBLE_Q 9
// # define LAST_EXIT 10

//--------------------- STRUCTURES -----------------------------

typedef struct s_redirection
{
	char				*file_name;
	int					type;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_cmd
{
	char			*value;
	char			**argv;
	int				argc;
	pid_t			pid;
	t_redirection	*redirection;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_varenv
{
	char			*name;
	char			*value;
	struct s_varenv	*next;
	struct s_varenv	*prev;
	bool			hiden;
}	t_varenv;

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
	int				type;
}	t_token;

typedef struct s_data
{
	t_cmd		*cmd_lst;
	t_varenv	*varenv_lst;
	t_token		*tok_lst;
	int			lst_exit;
	char		**histo;
}	t_data;

//--------------------- FONCTIONS -----------------------------

// SHELL INITIALIZATION
t_varenv	*init_varenv(char **envp);
void		init_minimalist_env(t_varenv **varenv_lst);
void		init_existing_env(t_varenv **varenv_lst, char **envp);
void		free_envp_on_error(char **envp, int i);
char		**convert_env_list_to_array(t_varenv *varenv_lst);
int			count_env_vars(t_varenv *varenv_lst);
char		*create_env_entry(t_varenv *varenv_lst);
void		append_varenv_node(t_varenv **varenv_lst, t_varenv *new_node);
void		create_varenv(t_varenv **varenv_lst, char *name, char *value,
				bool hiden);
void		free_varenv(t_varenv *varenv_lst);
void		free_varenv_node(t_varenv *node);
void		free_cmd_list(t_cmd *list);
void		free_token_list(t_token *list);

// READLINE MAIN LOOP
void		ft_start_minishell(t_data *data);

//LEXING
//Lexer
t_token						*lexer(char *line);

// utils
bool						ft_is_whitespace(char c);
int							have_to_close_tok(char c);
int							is_an_operator(int type);

// utils token
t_token						*ft_tok_new(void *content, int type);
t_token						*ft_toklast(t_token *lst);
void						ft_tokadd_back(t_token **lst, t_token *new);
t_token						*init_type_token_with_x_char_of_line(int type,
								t_token *token, int x, char *line, int i);//TODO trop de variables
void						free_token_list_l(t_token **list);//A modifier
// id_and_create_token
t_token						*token_type_operators(char *line, int i,
								t_token *new_token);
t_token						*token_type_varenv(char *line, int i,
								t_token *new_token);
t_token						*token_type_word(char *line, int i,
								t_token *new_token);
t_token						*create_token(char *line, int i,
								t_token *new_token);
// checker
int							check_lexing(t_token *head_of_list);

// EXECUTER
void		executer(t_data *data);

// REDIRECTIONS
void		apply_redirections(t_redirection *redirection);
void		merge_heredoc_and_input(int heredoc_fd, int input_fd);
void		handle_input_redirection(t_redirection *redirection, int *input_fd,
				t_redirection **last_heredoc, bool *input_redirection_found);
void		handle_output_redirections(t_redirection *redirection,
				int *last_output_fd);
void		handle_pipe_redirections(t_cmd *cmd, int pipe_in, int pipe_fd[2]);
void		close_redirections(t_redirection *redirection);
int			ft_strcmp(const char *s1, const char *s2);
void		setup_io_redirections(int heredoc_fd, int pipe_in, int pipe_fd[2],
				t_cmd *cmd);
void		read_and_write(int src_fd, int dest_fd);

// REDIRECTIONS - HEREDOC
int			ft_create_heredoc(const char *delimiter, int index);
bool		contains_heredoc(t_redirection *redirection);
void		process_heredoc_input(int fd, const char *delimiter);
void		unlink_heredoc_temp(t_redirection *redirection);
void		process_heredoc_input(int fd, const char *delimiter);
void		handle_heredocs_simple_cmd(t_redirection *redirection);
void		handle_heredocs_pipeline(t_cmd *cmd_lst);
void		handle_heredoc_redirection(t_redirection *last_heredoc,
				int *heredoc_fd);
void		setup_heredoc_fd(t_cmd *cmd, int *heredoc_fd);
void		create_heredoc_list(t_cmd *cmd_lst, char *last_heredoc_files[]);
void		handle_heredoc_input(char *heredoc_file);
void		create_heredoc_file(t_redirection *redir, int index);
void		generate_heredoc_filename(char *filename, int index);

// EXECUTER - SIMPLE CMD
void		execute_builtin(t_cmd *cmd, t_data *data);
bool		is_builtin(const char *cmd_value);
void		exec_simple_builtin(t_cmd *cmd, t_data *data);
void		exec_simple_extern_cmd(t_cmd *cmd, t_data *data);
void		executer_simple_cmd(t_cmd *cmd, t_data *data);

// EXECUTER - PIPELINE
void		execute_external_cmd(t_cmd *cmd, t_data *data);
void		executer_pipeline_cmd(t_cmd *cmd_lst, t_data *data);
void		setup_pipe(int pipe_fd[2]);
void		handle_parent_process_pipeline(pid_t pid, t_cmd *data,
				int *pipe_in, int pipe_fd[2]);
void		handle_child_process_pipeline(t_cmd *cmd, t_data *data,
				int pipe_in, int pipe_fd[2]);
void		cleanup_pipeline(t_cmd *cmd_lst);

// COMMAND PATH
char		*find_cmd_path(const char *cmd, t_varenv *varenv_lst);
int			count_env_vars(t_varenv *varenv_lst);

void		free_tab(char **tab);

// BUILT-IN COMMANDS
void		ft_echo(t_cmd *cmd);

#endif
