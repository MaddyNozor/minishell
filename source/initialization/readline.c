/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:41:57 by sabellil          #+#    #+#             */
/*   Updated: 2025/02/24 19:17:46 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

// void init_signals(void)
// {
//     signal(SIGINT, handle_sigint);  // gestion de ctrl+C
//     signal(SIGQUIT, SIG_IGN);      // ignorer ctrl+ backslash
// }

// t_token *lexer(char *input)
// {
//     (void)input;
// 	printf("Hey\n");
//     return (NULL); // Implémentation à compléter
// }

t_cmd	*parser(t_token *tok)
{
	(void)tok;
	return (NULL);
}

char	*read_user_input(void)
{
	char	*input;

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

void	ft_start_minishell(t_data *data)
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
			data->tok_lst = ft_spot_the_quotes(data);//TODO peut etre meme pas besoin du dat_tok_lst = ? Comme l'adresse du premier noeud va rester la meme 
		
		free_token_list(data->tok_lst);//TODO a virer une fois parsing fonctionnel
		// {
		// 	data->cmd_lst = parser(data->tok_lst);
		// 	if (data->cmd_lst)
		// 	{
		// 		executer(data);
		// 		free_cmd_list(data->cmd_lst);
		// 		data->cmd_lst = NULL;
		// 	}
		// 	free_token_list(data->tok_lst);
		// }
	}
}
