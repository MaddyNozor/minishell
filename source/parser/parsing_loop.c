/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:24:19 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/09 16:07:00 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

t_cmd	*init_cmd_structs(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->value = NULL;
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->pid = 0;
	cmd->redirection = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	handle_tokens(t_token *tok, t_cmd **cmd_list, t_varenv *varenv_lst)
{
	t_queue	*queue;
	t_cmd	*current_cmd;

	queue = init_queue();
	current_cmd = init_cmd_structs();
	*cmd_list = current_cmd;
	// printf("///////////Starting token handling.../////////////\n");
	while (tok)
	{
		if (!tok->content)
		{
			// printf("Warning: Encountered NULL token content. Skipping.\n");
			tok = tok->next;
			continue ;
		}
		// printf("Processing token: %s (type %d)\n", tok->content, tok->type);
		if (tok->type == PIPE)
		{
			handle_token_pipe(&current_cmd, queue); //OK
		}
		else if (tok->type == VAR_ENV) //OK MAIS TODO : Gerer les $? ici ?
		{
			handle_var_env(tok, queue, current_cmd, varenv_lst);
		}
		else if (tok->type == WORD)
		{
			handle_token_word(queue, &tok, current_cmd); //OK
		}
		else if (tok->type == REDIRECT_IN || tok->type == REDIRECT_OUT
					|| tok->type == APPEND_OUT || tok->type == HEREDOC)
		{
			handle_redirections(tok, &current_cmd, varenv_lst);
			tok = tok->next;// essayer de le mettre dans handle_redir_out pour racourcir mais is ok pour l'instant
		}
		// else if (tok->type == EOF)// A virer peut etre apres avoir tout code, pas besoin ?
		// {
		//     handle_endoffile(queue, current_cmd);
		// }
		tok = tok->next;
	}
	transfer_queue_to_argv(queue, current_cmd);
	// printf("Final command list after parsing:\n");// Juste pour le debug
	//         t_cmd *tmp_cmd = *cmd_list;
	//         int i;
	//         while (tmp_cmd)
	//         {
	//             printf("Command: %s, argc: %d\n", tmp_cmd->value, tmp_cmd->argc);
	//             if (tmp_cmd->argv)
	//             {
	//                 printf("  argv: ");
	//                 for (i = 0; tmp_cmd->argv[i]; i++)
	//                     printf("[%s] ", tmp_cmd->argv[i]);
	//                 printf("\n");
	//             }
	//             t_redirection *tmp_redir = tmp_cmd->redirection;
	//             while (tmp_redir)
	//             {
	//                 printf("  Redirection: file: %s, type: %d\n", tmp_redir->file_name, tmp_redir->type);
	//                 tmp_redir = tmp_redir->next;
	//             }
	//             tmp_cmd = tmp_cmd->next;
	//         }
	//         printf("Token handling completed.\n");
}

t_cmd	*parser(t_token *tok, t_varenv *varenv_lst)
{
	t_cmd	*cmd_list;

	cmd_list = NULL;
	if (!tok)
	{
		printf("No tokens to parse.\n");
		return (NULL);
	}
	// printf("STAAAAAAAAART : Starting parser...\n");
	// t_token *current_tok = tok; // Pour debug
	// while (current_tok)
	// {
	// 	printf("🔍 Token AVANT handle_tokens : %s, type = %d\n",
	// 		   current_tok->content, current_tok->type);
	// 	current_tok = current_tok->next;
	// }
	handle_tokens(tok, &cmd_list, varenv_lst);
	// t_cmd *current_cmd = cmd_list;
	// while (current_cmd)
	// {
	// 	printf("\n🔹 Commande trouvée : %s\n", current_cmd->value);
	// 	printf("   📌 Nombre d'arguments : %d\n", current_cmd->argc);
	// 	if (current_cmd->argv)
	// 	{
	// 		printf("   📌 Arguments : ");
	// 		for (int i = 0; current_cmd->argv[i]; i++)
	// 			printf("[%s] ", current_cmd->argv[i]);
	// 		printf("\n");
	// 	}
		// t_redirection *redir = current_cmd->redirection;
		// while (redir)
		// {
		// 	printf("   🔍 Redirection détectée : fichier = %s, type = %d\n",
		// 		   redir->file_name, redir->type);
		// 	redir = redir->next;
		// }
		// current_cmd = current_cmd->next;
	// }
	// printf("\nParsing completed. On move on to executer!!\n");
	return (cmd_list);
}
