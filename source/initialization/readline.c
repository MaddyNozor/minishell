/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:41:57 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 13:08:22 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

char	*read_user_input(t_data *data)
{
	char	*input;
	int		new_stdin;

	ft_init_signal_handlers();
	if (isatty(STDIN_FILENO) == 0)
	{
		new_stdin = open("/dev/tty", O_RDONLY);
		if (new_stdin == -1)
			exit_with_error(data, "STDIN", "Erreur réouverture", 1);
		if (dup2(new_stdin, STDIN_FILENO) == -1)
		{
			close(new_stdin);
			exit_with_error(data, "dup2", "Erreur de duplication", 1);
		}
		close(new_stdin);
	}
	input = readline("minishell$ ");
	if (!input)
	{
		clear_history();
		exit_error_rdl(data, "readline", "Error reading input", 1);
	}
	if (*input)
		add_history(input);
	return (input);
}

void	ft_start_minishell(t_data *data)
{
	char	*input;

	while (1)
	{
		input = read_user_input(data);
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		data->tok_lst = lexer(data, input);
		free(input);
		if (!data->tok_lst)
			continue ;
		data->tok_lst = ft_spot_the_quotes(data);
		data->cmd_lst = parser(data->tok_lst, data->varenv_lst, data);
		if (data->cmd_lst)
		{
			executer(data);
			update_exit_status(data, data->lst_exit);
			free_cmd_list(data->cmd_lst);
			data->cmd_lst = NULL;
		}
		free_token_list(&data->tok_lst);
	}
}
