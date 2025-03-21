/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:41:57 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/21 13:35:20 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"


// void init_signals(void)//TODO : A virer ?
// {
//     signal(SIGINT, handle_sigint);  // gestion de ctrl+C
//     signal(SIGQUIT, SIG_IGN);      // ignorer ctrl+ backslash
// }

// char	*read_user_input(t_data *data)
// {
// 	char	*input;
// 	int		new_stdin;

// 	ft_init_signal_handlers();
// 	if (isatty(STDIN_FILENO) == 0) // Évite d'afficher un prompt après un heredoc
// 	{
// 		new_stdin = open("/dev/tty", O_RDONLY);
// 		if (new_stdin == -1)
// 			exit_with_error(NULL, "STDIN", "Erreur réouverture", 1);
// 		dup2(new_stdin, STDIN_FILENO);
// 		close(new_stdin);
// 	}
// 	input = readline("minishell$ ");
// 	if (!input)
// 	{
// 		clear_history();
// 		// exit_with_error_readline(NULL, "readline", "", 0); // Pas de message d'erreur
// 		exit_with_error_readline(data, "readline", "", 0);
// 	}
// 	if (*input)
// 		add_history(input);
// 	return (input);
// }

char *read_user_input(t_data *data)
{
    char *input;
    int new_stdin;

    ft_init_signal_handlers();
    if (isatty(STDIN_FILENO) == 0) // Évite d'afficher un prompt après un heredoc
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
        clear_history(); // Nettoie l'historique de commandes
        exit_with_error_readline(data, "readline", "Error reading input", 1);
    }
    if (*input)
        add_history(input);
    return input;
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
		data->tok_lst = lexer(input);
		free(input);
		if (!data->tok_lst)
			continue ;

		data->tok_lst = ft_spot_the_quotes(data);
		data->cmd_lst = parser(data->tok_lst, data->varenv_lst, data);
		if (data->cmd_lst)
		{
			executer(data);
			// update_exit_status(data->varenv_lst, data->lst_exit);
			update_exit_status(data, data->lst_exit);
			free_cmd_list(data->cmd_lst);
			data->cmd_lst = NULL;
		}
		free_token_list(&data->tok_lst);
	}
}




// char	*read_user_input(void)//TODO : A virer ajout de lst_exit (2003, tests exec OK juste avant ce changement)
// {
// 	char	*input;
	
// 	ft_init_signal_handlers();
//     if (isatty(STDIN_FILENO) == 0)//Pour pas avoir le reste d'un heredoc passe en prompt
//     {
//         // printf("⏩ STDIN est fermé, on le rouvre !\n");
//         int new_stdin = open("/dev/tty", O_RDONLY);
//         if (new_stdin == -1)
//         {
//             perror("Erreur réouverture STDIN");
//             exit(1);
//         }
//         dup2(new_stdin, STDIN_FILENO);
//         close(new_stdin);
//     }
// 	input = readline("minishell$ ");
// 	if (!input)
// 	{
// 		clear_history();
// 		exit(0);
// 	}
// 	if (*input)
// 		add_history(input);
// 	return (input);
// }

// void ft_start_minishell(t_data *data)//TODO : A virer ajout de lst_exit (2003, tests exec OK juste avant ce changement)
// {
//     char *input;

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
// 		if (data->tok_lst)
// 		{			
//             data->tok_lst = ft_spot_the_quotes(data);
// 			data->cmd_lst = parser(data->tok_lst, data->varenv_lst, data);
// 			if (data->cmd_lst)
// 			{
// 				executer(data);
// 				free_cmd_list(data->cmd_lst);
// 				data->cmd_lst = NULL;
// 			}
// 			free_token_list(data->tok_lst);
// 		}
// 	}
// }
