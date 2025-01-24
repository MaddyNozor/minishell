/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:41:57 by sabellil          #+#    #+#             */
/*   Updated: 2025/01/24 14:37:50 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

// void init_signals(void)
// {
//     signal(SIGINT, handle_sigint);  // gestion de ctrl+C
//     signal(SIGQUIT, SIG_IGN);      // ignorer ctrl+\
// }

t_token *lexer(char *input)
{
    (void)input;
	printf("Hey\n");
    return NULL; // Implémentation à compléter
}

t_cmd *parser(t_token *tok)
{
    (void)tok;
    return NULL; // Implémentation à compléter
}

void executer(t_data *data, char **envp)
{
    (void)data;
    (void)envp;
    // Implémentation à compléter
}

char	*read_user_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
	{
		write(1, "exit\n", 5);
		rl_clear_history();
		exit(0);
	}
	if (*input)
		add_history(input); // TODO : free history quand exit ou ctrl-d
	return (input);
}

void	free_cmd_list(t_cmd *list)
{
	t_cmd			*tmp;
	t_redirection	*redir_tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->value);
		while (tmp->redirection)
		{
			redir_tmp = tmp->redirection;
			tmp->redirection = tmp->redirection->next;
			free(redir_tmp->file_name);
			free(redir_tmp);
		}
		free(tmp->argv);
		free(tmp);
	}
}

void	free_token_list(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->content);
		free(tmp);
	}
}

void	ft_start_minishell(t_data *data, char **envp)
{
	char	*input;

	while (1)
	{
		input = read_user_input();
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		data->tok_lst = lexer(input);
		free(input);
		if (data->tok_lst)
		{
			data->cmd_lst = parser(data->tok_lst);
			if (data->cmd_lst)
			{
				executer(data, envp);
				free_cmd_list(data->cmd_lst);
				data->cmd_lst = NULL;
			}
			free_token_list(data->tok_lst);
			data->tok_lst = NULL;
		}
	}
}

// // POUR TESTER READLINE UNIQUEMENT
