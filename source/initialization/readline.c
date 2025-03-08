/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:41:57 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/08 16:18:08 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

// void init_signals(void)
// {
//     signal(SIGINT, handle_sigint);  // gestion de ctrl+C
//     signal(SIGQUIT, SIG_IGN);      // ignorer ctrl+\
// }

char	*read_user_input(void)
{
	char	*input;
    if (isatty(STDIN_FILENO) == 0)//Pour pas avoir le reste d'un heredoc passe en prompt
    {
        printf("⏩ STDIN est fermé, on le rouvre !\n");
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
		write(1, "exit\n", 5);
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
            continue;
        }
        data->tok_lst = lexer(input);
        free(input);
        if (data->tok_lst)
        {
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
// void	ft_start_minishell(t_data *data)// la fonction de base
// {
// 	char	*input;

// 	while (1)
// 	{
// 		input = read_user_input();
// 		if (*input == '\0')
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		data->tok_lst = lexer(input);
// 		free(input);
// 		// free_token_list(data->tok_lst);
// 		if (data->tok_lst)
// 		{
// 			data->cmd_lst = parser(data->tok_lst);
// 			// printf("Executing data:");
// 			// t_cmd *tmp_cmd = data->cmd_lst;
// 			// while (tmp_cmd)
// 			// {
// 			// 	printf("Command: %s, argc: %d", tmp_cmd->value, tmp_cmd->argc);
// 			// 	tmp_cmd = tmp_cmd->next;
// 			// }
// 			if (data->cmd_lst)
// 			{
// 				printf("On rentre dans executer\n");
// 				executer(data);
// 				free_cmd_list(data->cmd_lst);
// 				data->cmd_lst = NULL;
// 			}
// 			free_token_list(data->tok_lst);
// 		}
// 	}
// }