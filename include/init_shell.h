/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:50:26 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 12:04:55 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_SHELL_H
# define INIT_SHELL_H

//--------------------- INCLUDES -----------------------------
# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h> 
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>

//--------------------- DEFINES -----------------------------
# define FALSE 0
# define TRUE 1
# define FAILURE 0
# define SUCCESS 1

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

//--------------------- STRUCTURES -----------------------------

typedef struct s_redirection
{
	char					*file_name;
	int						type;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_varenv
{
	char					*name;
	char					*value;
	struct s_varenv			*next;
	struct s_varenv			*prev;
	bool					hiden;
}							t_varenv;

typedef struct s_token
{
	char					*content;
	struct s_token			*next;
	struct s_token			*prev;
	int						type;
	int						nb_quote;
	bool					quote_added;
}							t_token;

typedef struct s_cmd
{
	char					*value;
	char					**argv;
	int						argc;
	pid_t					pid;
	t_redirection			*redirection;
	struct s_cmd			*next;
	struct s_data			*data;
}							t_cmd;

typedef struct s_data
{
	t_cmd					*cmd_lst;
	t_varenv				*varenv_lst;
	t_token					*tok_lst;
	char					*secret_path;
	int						lst_exit;
}							t_data;

typedef struct s_node
{
	char					*content;
	struct s_node			*next;
}							t_node;

typedef struct s_queue
{
	t_node					*head;
	t_node					*tail;
}							t_queue;

typedef struct s_pipe_data
{
	int	heredoc_fd;
	int	pipe_in;
	int	pipe_fd[2];
}							t_pipe_data;

typedef struct s_redir_state
{
	int						last_output_fd;
	int						input_fd;
	t_redirection			*last_heredoc;
	bool					input_redir_found;
	bool					output_created;
}							t_redir_state;

typedef struct s_varenv_data
{
	char					*name;
	char					*value;
	bool					hiden;
}							t_varenv_data;

//--------------------- FONCTIONS -----------------------------

// SHELL INITIALIZATION
t_varenv	*init_varenv(char **envp, t_data *data);
void		init_minimalist_env(t_varenv **varenv_lst, t_data *data);
void		free_envp_on_error(char **envp, int i);
char		**convert_env_list_to_array(t_data *data, t_varenv *varenv_lst);
int			count_env_vars(t_varenv *varenv_lst);
char		*create_env_entry(t_data *data, t_varenv *varenv_lst);
void		append_varenv_node(t_varenv **varenv_lst, t_varenv *new_node);
void		create_varenv(t_data *data, t_varenv **varenv_lst,
				t_varenv_data var_data);
void		free_varenv(t_varenv *varenv_lst);
void		free_varenv_node(t_varenv *node);
void		free_cmd_list(t_cmd *list);
void		free_token_list(t_token **list);

// SIGNALS
void		ft_init_signal_handlers(void);
void		sig_int_handler(sig_atomic_t g_sig_caught);
void		sig_int_handler_fork(sig_atomic_t g_sig_caught);

// READLINE MAIN LOOP
void		ft_start_minishell(t_data *data);

// LEXING
t_token		*lexer(char *line);

// utils
bool		ft_is_whitespace(char c);
int			have_to_close_tok(char c);
int			is_an_operator(int type);
int			ft_size_according_to_type(int type);
t_token		*ft_tok_new(void *content, int type);
t_token		*ft_toklast(t_token *lst);
void		ft_tokadd_back(t_token **lst, t_token *new);
t_token		*init_type_token_with_x_char_of_line(int type, int x,
				char *line, int i);

// id_and_create_token
int			ft_type_detector(char *line, int i);
t_token		*token_type_operators(char *line, int i, t_token *new_token);
t_token		*token_type_word(char *line, int i, t_token *new_token);
t_token		*create_token(char *line, int i, t_token *new_token);

// checker
int			check_lexing(t_token *head_of_list);

// PARSING QUOTES
char		*ft_trim_quote(char const *s1, char const q);
char		*ft_glue_the_slices_again(t_list *list_slice);
char		*ft_cut_normal_text(char *content, int *i, char quote_type);
char		*ft_cut_quoted_text(char *content, int *i,
				t_varenv *lst, bool prev_hd);
char		*ft_cut_a_slice(char *content, int *i, t_varenv *lst,
				bool prev_hd);
void		ft_stock_the_slice(t_list **stock_list, char *slice);
char		*ft_quote_manager(char *actual_content, t_varenv *lst,
				bool prev_hd);
t_token		*ft_spot_the_quotes(t_data *data);
char		*ft_varenv_manager(char *string, t_varenv *lst);
char		*ft_varenv_slicing(char *content, int *i, t_varenv *lst);
char		*ft_cut_varenv(char *content, int *i);
char		*ft_cut_normal_text_but_varenv(char *content, int *i);
char		*ft_expand_varenv(char *var_found, t_varenv *varenv);

// EXECUTER
void		executer(t_data *data);

// REDIRECTIONS
void		apply_redirections(t_redirection *redirection, t_data *data);
void		merge_heredoc_and_input(t_data *data, int heredoc_fd, int input_fd);
void		handle_input_redirection(t_redirection *redirection, int *input_fd,
				t_redirection **last_heredoc, bool *input_redir_found);
void		handle_output_redirections(t_redirection *redir, t_data *data,
				int *last_out_fd);
void		handle_pipe_redirections(t_cmd *cmd, int pipe_in, int pipe_fd[2]);
void		close_redirections(t_redirection *redirection);
int			ft_strcmp(const char *s1, const char *s2);
void		read_and_write(t_data *data, int src_fd, int dest_fd);

// REDIRECTIONS - HEREDOC
bool		contains_heredoc(t_redirection *redirection);
void		unlink_heredoc_temp(t_data *data, t_redirection *redirection);
void		process_heredoc_input(t_data *data, int fd, const char *delimiter);

void		handle_heredocs_simple_cmd(t_data *data,
				t_redirection *redirection);
void		handle_heredocs_pipeline(t_data *data, t_cmd *cmd_lst);
void		handle_heredoc_redirection(t_data *data,
				t_redirection *last_heredoc, int *heredoc_fd);
void		create_heredoc_list(t_cmd *cmd_lst, char *last_heredoc_files[]);
void		handle_heredoc_input(t_data *data, char *heredoc_file);
void		create_heredoc_file(t_data *data, t_redirection *redir, int index);
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
void		setup_pipe(t_data *data, int pipe_fd[2]);
void		cleanup_pipeline(t_data *data, t_cmd *cmd_lst);

// EXECUTER - COMMAND PATH
char		*find_cmd_path(const char *cmd, t_varenv *varenv_lst, t_data *data);
int			count_env_vars(t_varenv *varenv_lst);
void		free_tab(char **tab);

// BUILT-IN COMMANDS
int			ft_echo(t_cmd *cmd, t_data *data);
int			ft_pwd(t_data *data);
int			ft_env(t_data *data, t_cmd *cmd);
int			ft_cd(t_cmd *cmd, t_data *data);
void		ft_exit(t_cmd *cmd, t_data *data);
int			ft_unset(t_data *data, t_cmd *cmd);
int			ft_export(t_data *data, t_cmd *cmd);
bool		handle_invalid_identifier(char *arg, int *error_flag);
bool		extract_name_value(char *arg, char **name, char **value);
bool		is_valid_identifier(char *name);
void		ft_print_list_export(t_data *data);

// PARSER - QUEUE
void		transfer_queue_to_argv(t_queue *queue, t_cmd *cmd);
bool		enqueue_token(t_queue *queue, char *content, t_data *data);
t_queue		*init_queue(t_data *data);

// PARSER - MAIN LOOP
t_cmd		*parser(t_token *tok, t_varenv *varenv_lst, t_data *data);
t_cmd		*init_cmd_structs(t_data *data);

// PARSER - TOKEN_PIPE
void		handle_token_pipe(t_cmd **current_cmd, t_queue *queue);
// PARSER - TOKEN_VAR_ENV
void		handle_var_env(t_token *tok, t_queue *queue, t_cmd *current_cmd,
				t_varenv *varenv);
void		replace_var(t_token *tok, char *new_content);
bool		ft_var_exists(char *var_name, t_varenv *varenv);
char		*ft_expand(char *var_name, t_varenv *varenv);

// PARSER - TOKEN_REDIRECTIONS
void		handle_redirections(t_token *tok, t_cmd **current_cmd,
				t_varenv *varenv);
void		handle_heredoc(t_token *tok, t_cmd **current_cmd, t_varenv *varenv,
				int redir_type);

//PARSER - AUTRES TOKENS
void		handle_token_word(t_queue *queue, t_token **tok,
				t_cmd *current_cmd);
char		*get_env_value(t_varenv *varenv_lst, const char *key);
void		handle_heredoc_and_input(t_data *data, int heredoc_fd,
				int input_fd);

//EXIT
char		*get_exit_status(t_varenv *varenv);
void		update_exit_status(t_data *data, int exit_status);
void		exit_with_error(t_data *data, char *context, char *error_message,
				int exit_code);
void		exit_error_rdl(t_data *data, char *ctxt, char *err_msg,
				int exit_code);
bool		update_env_var(t_varenv *varenv, char *key, char *value);

//FREE THE MINISHELL
void		ft_free_all(t_data *data);
void		free_queue(t_queue *queue);

#endif
