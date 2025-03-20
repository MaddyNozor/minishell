/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:41:57 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/20 18:11:23 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"


// void init_signals(void)
// {
//     signal(SIGINT, handle_sigint);  // gestion de ctrl+C
//     signal(SIGQUIT, SIG_IGN);      // ignorer ctrl+ backslash
// }

char	*read_user_input(void)
{
	char	*input;
	
	ft_init_signal_handlers();
    if (isatty(STDIN_FILENO) == 0)//Pour pas avoir le reste d'un heredoc passe en prompt
    {
        // printf("⏩ STDIN est fermé, on le rouvre !\n");
        int new_stdin = open("/dev/tty", O_RDONLY);
        if (new_stdin == -1)
        {
            perror("Erreur réouverture STDIN");
            exit(1);
        }
        dup2(new_stdin, STDIN_FILENO);
        close(new_stdin);
    }
	input = readline("minishell$ ");
	if (!input)
	{
		clear_history();
		exit(0);
	}
	if (*input)
		add_history(input);
	return (input);
}

void ft_start_minishell(t_data *data)
{
    char *input;

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
            data->tok_lst = ft_spot_the_quotes(data);
			data->cmd_lst = parser(data->tok_lst, data->varenv_lst);
			if (data->cmd_lst)
			{
				executer(data);
				free_cmd_list(data->cmd_lst);
				data->cmd_lst = NULL;
			}
			free_token_list(data->tok_lst);
		}
	}
}
// TODO:
// else
// data->lst_exit = FAILURE;