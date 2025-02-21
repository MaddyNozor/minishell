/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/02/21 15:10:25 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

// int	main(int ac, char **av, char **envp)
// {
// 	t_data	data;

// 	if (ac != 1)
// 		return (1);
// 	(void)av;
// 	ft_bzero(&data, sizeof(t_data));
// 	data.varenv_lst = init_varenv(envp);
// 	ft_start_minishell(&data, envp);
// 	// ft_free_all(data);
// 	return (0);
// }
int main(int argc, char **argv, char **envp)
{
    t_data data;
    t_cmd cmd1, cmd2, cmd3;
    t_varenv *env_list;
    t_redirection redir_A, redir_B, redir_C;

    (void)argc;
    (void)argv;

    // 🔹 Initialisation de l'environnement
    env_list = init_varenv(envp);
    data.varenv_lst = env_list;
    data.lst_exit = 0;

    // 🔹 Configuration des heredocs (`<< A`, `<< B`, `<< C`)
    ft_bzero(&redir_A, sizeof(t_redirection));
    redir_A.type = REDIR_HEREDOC;
    redir_A.file_name = strdup("A");
    redir_A.next = NULL;  // Pas de chaînage ici !

    ft_bzero(&redir_B, sizeof(t_redirection));
    redir_B.type = REDIR_HEREDOC;
    redir_B.file_name = strdup("B");
    redir_B.next = NULL;  // Pas de chaînage ici !

    ft_bzero(&redir_C, sizeof(t_redirection));
    redir_C.type = REDIR_HEREDOC;
    redir_C.file_name = strdup("C");
    redir_C.next = NULL;  // Pas de chaînage ici !

    // 🔹 Commande 1 : `cat << A`
    ft_bzero(&cmd1, sizeof(t_cmd));
    cmd1.value = strdup("cat");
    cmd1.argv = (char *[]){"cat", NULL};
    cmd1.argc = 1;
    cmd1.redirection = &redir_A;  // `cat` utilise SEULEMENT `A`
    cmd1.next = &cmd2;

    // 🔹 Commande 2 : `cat << B`
    ft_bzero(&cmd2, sizeof(t_cmd));
    cmd2.value = strdup("cat");
    cmd2.argv = (char *[]){"cat", NULL};
    cmd2.argc = 1;
    cmd2.redirection = &redir_B;  // `cat` utilise SEULEMENT `B`
    cmd2.next = &cmd3;

    // 🔹 Commande 3 : `cat << C`
    ft_bzero(&cmd3, sizeof(t_cmd));
    cmd3.value = strdup("cat");
    cmd3.argv = (char *[]){"cat", NULL};
    cmd3.argc = 1;
    cmd3.redirection = &redir_C;  // `cat` utilise SEULEMENT `C`
    cmd3.next = NULL;  // Dernière commande du pipeline

    // 🔹 Configuration du pipeline
    data.cmd_lst = &cmd1;

    // 🔹 Affichage du test
    printf("\n🔽🔽🔽 Test PIPELINE avec plusieurs HEREDOCS 🔽🔽🔽\n");
    printf("▶ Exécution : cat << A | cat << B | cat << C\n");
    printf("----------------------------------------------------\n");

    // 🔹 Exécuter la commande via `executer`
    executer(&data);

    // 🔹 Nettoyage mémoire
    free(cmd1.value);
    free(cmd2.value);
    free(cmd3.value);
    free(redir_A.file_name);
    free(redir_B.file_name);
    free(redir_C.file_name);
    free_varenv(data.varenv_lst);

    return 0;
}
