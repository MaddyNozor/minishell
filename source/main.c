/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/21 13:07:59 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

volatile sig_atomic_t g_sig_caught = 0;

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	
	if (ac != 1)
		return (1);
	(void)av;
	ft_bzero(&data, sizeof(t_data));
	data.lst_exit = 0;//Ajout 21
	data.varenv_lst = init_varenv(envp, &data);
	ft_init_signal_handlers();
	ft_start_minishell(&data);
	// ft_free_all(&data);
	return (0);
}

// // A GERER 
// ➜  minishell git:(verif-exec) ✗ ./minishell             
// minishell$ echo sara > ins
// minishell$ cat < ins
// sara
// minishell$ echo sss < sjjsjs PLANTE
// bash: sjjsjs: No such file or directory

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

// bash-5.1$ echo "Hello World" | cat
// Hello World

// bash-5.1$ echo "Hello World" | tr ' ' '_'
// Hello_World

// bash-5.1$ echo "Hello World" | tr ' ' '_' | rev
// dlroW_olleH



// bash-5.1$ echo Sara | lsssssssssss | ls
// bash: lsssssssssss: command not found
//  biiinii
//  c_formatter_42
//  Desktop
//  Documents
//  Downloads


// bash-5.1$ ls | echo Sara
// Sara

// bash-5.1$ ls | wc -l | echo Sara
// Sara

// bash-5.1$ echo Sara | ls | wc -l
// 26

// bash-5.1$ echo Sara | wc -l | ls
//  biiinii
//  c_formatter_42
//  Desktop
//  Documents
//  Downloads
//  fichier1
//  goinfre
//  ilona
//  intra-uuid-853640af-6d79-45c8-965a-5726ed79af59-6151788-sabellil
//  kdjkfdh
//  Music
//  output
//  output2
//  output_test_file1
//  philo
//  philotest
//  Pictures
//  pipex
//  Public
// 'Save changement'
//  sgoinfre
//  snap
//  Templates
//  try
//  Videos
//  zzzzzzzzzzzzzzzzzzzzz
// bash-5.1$ 






// bash-5.1$ cat << A | tr 'a-z' 'A-Z' | cat << B | rev
// > Oui
// > A
// > Non
// > B
// noN
// bash-5.1$ 

// bash-5.1$  cat << EOF | tr 'a-z' 'A-Z' | rev
// > Oui
// > EOF
// IUO
// bash-5.1$ 


// bash-5.1$ cat << A << B << C | tr 'a-z' 'A-Z' | rev
// > Oui
// > A
// > Non
// > B
// > Pourquoi
// > C
// IOUQRUOP
// bash-5.1$ cat << A << B << C | tr 'a-z' 'A-Z' | lssss | rev
// > Oui
// > A
// > Non
// > B
// > Pourquoi
// > C
// bash: lssss: command not found
// bash-5.1$ 


// bash-5.1$ cat << EOF1 << EOF2 | tr 'a-z' 'A-Z' | rev << EOF3 << EOF4
// > Oui
// > EOF1
// > Non
// > EOF2
// > Pourquoi
// > EOF3
// > Pas
// > EOF4
// saP
// bash-5.1$ 


// bash-5.1$ cat << EOF1 << EOF2 | lssss | tr 'a-z' 'A-Z' | rev << EOF3 << EOF4
// > Oui
// > EOF1
// > Non
// > EOF2
// > Pourquoi
// > EOF3
// > Pas
// > EOF4
// bash: lssss: command not found
// saP
// bash-5.1$ 





// bash-5.1$ cat << EOF << EOF < input.txt | tr 'a-z' 'A-Z' > output.txt // Affiche NON et pas output.txt nexiste pas
// > Oui
// > EOF
// > non
// > EOF
// bash: input.txt: No such file or directory
// bash-5.1$ 






// bash-5.1$ echo "Hello Minishell" | tr ' ' '_' > output.txt // affiche Hello Minishell en terminal
// bash-5.1$ cat output.txt
// Hello_Minishell
// bash-5.1$ 


// bash-5.1$ cat << A | tr 'a-z' 'A-Z' | lssssss | cat << B | rev
// > Oui
// > A
// > Non
// > B
// bash: lssssss: command not found
// noN
// bash-5.1$ 

// bash-5.1$ cat << EOF1 << EOF2 | tr 'a-z' 'A-Z' | lss |  rev << EOF3 << EOF4 // 
// > Oui
// > EOF1
// > Non
// > EOF2
// > Pourquoi
// > EOF3
// > Pas
// > EOF4
// saP
// bash: lss: command not found

// cat << EOF1 << EOF2 | tr 'a-z' 'A-Z' | lss |  rev << EOF3 << EOF4
// > Oui
// > EOF1
// > Non
// > EOF2
// > Pourquoi
// > EOF3
// > Pas
// > EOF4
// bash: lss: command not found
// saP

// << EOF

//LES DERNIERS TRUCS MAIS IS IT REALLY A PROBLEM ????

// bash-5.1$ ls | lsssssssssss | echo Sara  // EXECUTE MAIS INVERSE LIGNE, seul cas trouve
// Sara
// bash: lsssssssssss: command not found