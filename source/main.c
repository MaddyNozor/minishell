/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/14 16:05:20 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	
	if (ac != 1)
		return (1);
	(void)av;
	ft_bzero(&data, sizeof(t_data));
	data.varenv_lst = init_varenv(envp);
	ft_start_minishell(&data);
	//ft_free_all(data);
	return (0);
}

// #include "init_shell.h"

// int main(int argc, char **argv, char **envp) {
//     t_data data;
//     t_cmd cmd1;
//     t_varenv *env_list;
//     t_redirection redir_heredoc;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation de l'environnement
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Configuration du heredoc (`<< EOF`)
//     redir_heredoc.type = HEREDOC;
//     redir_heredoc.file_name = strdup("EOF");
//     redir_heredoc.next = NULL;

//     // 🔹 Commande : `cat << EOF`
//     cmd1.value = strdup("cat");
//     cmd1.argv = (char *[]){"cat", NULL};
//     cmd1.argc = 1;
//     cmd1.redirection = &redir_heredoc;
//     cmd1.next = NULL;  // 🔹 Pas de pipeline, commande unique

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd1;
//     data.lst_exit = 0;

//     // 🔹 Exécution du test
//     printf("\n🔽🔽🔽 DÉBUT DU TEST HEREDOC 🔽🔽🔽\n");
//     printf("▶ Exécution de : cat << EOF\n");
//     printf("----------------------------------------------------\n");

//     executer(&data);  // 🔹 Exécuter `cat << EOF`

//     printf("----------------------------------------------------\n");
//     printf("🔼🔼🔼 FIN DU TEST HEREDOC 🔼🔼🔼\n");

//     // 🔹 Nettoyage mémoire
//     free(cmd1.value);
//     free(redir_heredoc.file_name);
//     free_varenv(data.varenv_lst);

//     return 0;
// }




// TODO RESTE A FAIRE
//- Verif leak lexing-quote (Maddy) DONE !
//- Faire un fichier qui filtre les leak rl (exemple : echo Sara) (Maddy)
//- Signaux (Maddy)
//- Tests de redirections (avec et sans pipe) (Sara)
//- Verifier attente process parent de l'enfant - sleep (Sara)
//- ft_exit et code last_exit (Sara) a stocker en var env $? 
//- Verif leak (Sara)
//- ft_free_all (On voit apres, Maddy ?)
//- Builtin unset (A voir)
//- Builtin export (A voir)
// NB : Si jamais apres exec, le programme quitte tout seul (donner a Sara l'exemple de ligne de commande)


// bash-5.1$ ls | caaaaat | ouiiiii
// bash: ouiiiii: command not found
// bash: caaaaat: command not found
// bash-5.1$ 

// bash-5.1$ caaaaaat | ls
// bash: caaaaaat: command not found
//  jexiste   minishell   minishellavantclean09   philo   Sara  'Save Esca'
// bash-5.1$ 


// bash-5.1$ caaaaaat | ls | ouiiiii
// bash: ouiiiii: command not found
// bash: caaaaaat: command not found
// bash-5.1$ 


// bash-5.1$ caaaaaat | ls | ouiiiii | cat jexiste
// bash: caaaaaat: command not found
// bash: ouiiiii: command not found
// sara
// bash-5.1$ 


// bash-5.1$ ls | cat jexiste
// sara
// bash-5.1$ 


// bash-5.1$ cat jexiste | ls
//  jexiste   minishell   minishellavantclean09   philo   Sara  'Save Esca'
// bash-5.1$ 


// bash-5.1$ cat jexiste | ls | oui | cat jexiste2
// bash: oui: command not found
// bel
// bash-5.1$ cat jexiste | ls | cat jexiste2 | oui
// bash: oui: command not found
// bash-5.1$ 
//  verifier ca
//  minishell$ ls | echo Sara
// minishell$ 