// // TEST REDIR_IN < [cat < input_test_file] OK
// int main(void)
// {
//     t_cmd cmd;
//     t_redirection redir_in;

//     // Initialisation de la redirection d'entrée
//     ft_bzero(&redir_in, sizeof(t_redirection));
//     redir_in.type = REDIR_IN;
//     redir_in.file_name = "input_test_file"; // Fichier d'entrée
//     redir_in.next = NULL;

//     // Création du fichier d'entrée pour le test
//     system("echo 'Hello from input file' > input_test_file");

//     // Initialisation de la commande
//     ft_bzero(&cmd, sizeof(t_cmd));
//     cmd.value = "cat";
//     cmd.argv = (char *[]){"cat", NULL};
//     cmd.redirection = &redir_in;

//     // Appliquer la redirection et exécuter
//     printf("\nTest REDIR_IN avec la commande : cat < input_test_file\n");
//     apply_redirections(cmd.redirection);
//     execvp(cmd.value, cmd.argv); // Exécute la commande

//     return 0;
// }

// // TEST REDIR_OUT < [echo "Hello, World!" > output_test_file] OK
// int main(void)
// {
//     t_cmd cmd;
//     t_redirection redir_out;

//     // Initialisation de la redirection de sortie
//     ft_bzero(&redir_out, sizeof(t_redirection));
//     redir_out.type = REDIR_OUT;
//     redir_out.file_name = "output_test_file";
//     redir_out.next = NULL;

//     // Initialisation de la commande
//     ft_bzero(&cmd, sizeof(t_cmd));
//     cmd.value = "echo";
//     cmd.argv = (char *[]){"echo", "Hello, World!", NULL};
//     cmd.redirection = &redir_out;

//     // Appliquer la redirection et exécuter
//     printf("\nTest REDIR_OUT avec la commande : echo 'Hello, World!' > output_test_file\n");
//     apply_redirections(cmd.redirection);
//     execvp(cmd.value, cmd.argv);

//     return 0;
// }

// // TEST APPEND < [echo "Appended content" >> append_test_file] OK
// int main(void)
// {
//     t_cmd cmd;
//     t_redirection redir_append;

//     // Initialisation de la redirection append
//     ft_bzero(&redir_append, sizeof(t_redirection));
//     redir_append.type = REDIR_APPEND;
//     redir_append.file_name = "append_test_file";
//     redir_append.next = NULL;

//     // Création d'un fichier initial
//     system("echo 'Initial content' > append_test_file");

//     // Initialisation de la commande
//     ft_bzero(&cmd, sizeof(t_cmd));
//     cmd.value = "echo";
//     cmd.argv = (char *[]){"echo", "Appended content", NULL};
//     cmd.redirection = &redir_append;

//     // Appliquer la redirection et exécuter
//     printf("\nTest REDIR_APPEND avec la commande : echo 'Appended content' >> append_test_file\n");
//     apply_redirections(cmd.redirection);
//     execvp(cmd.value, cmd.argv);

//     return 0;
// }

// // TEST HEREDOC << [cat << EOF] OK
// int main(void)
// {
//     t_cmd cmd;
//     t_redirection redir_heredoc;

//     // Initialisation de la redirection heredoc
//     ft_bzero(&redir_heredoc, sizeof(t_redirection));
//     redir_heredoc.type = REDIR_HEREDOC;
//     redir_heredoc.file_name = "EOF"; // Délimiteur heredoc
//     redir_heredoc.next = NULL;

//     // Initialisation de la commande
//     ft_bzero(&cmd, sizeof(t_cmd));
//     cmd.value = "cat";
//     cmd.argv = (char *[]){"cat", NULL};
//     cmd.redirection = &redir_heredoc;

//     // Appliquer la redirection et exécuter
//     printf("\nTest REDIR_HEREDOC avec la commande : cat << EOF\n");
//     printf("Entrez votre texte suivi de 'EOF' pour terminer :\n");
//     apply_redirections(cmd.redirection);
//     execvp(cmd.value, cmd.argv);

//     return 0;
// }

// // TEST COMBO [cat < input_test_file > output_test_file] OK
// int main(void)
// {
//     t_cmd cmd;
//     t_redirection redir_in, redir_out;

//     // Initialisation des redirections
//     ft_bzero(&redir_in, sizeof(t_redirection));
//     redir_in.type = REDIR_IN;
//     redir_in.file_name = "input_test_file";
//     redir_in.next = &redir_out;

//     ft_bzero(&redir_out, sizeof(t_redirection));
//     redir_out.type = REDIR_OUT;
//     redir_out.file_name = "output_test_file";
//     redir_out.next = NULL;

//     // Création des fichiers pour le test
//     system("echo 'Input content' > input_test_file");

//     // Initialisation de la commande
//     ft_bzero(&cmd, sizeof(t_cmd));
//     cmd.value = "cat";
//     cmd.argv = (char *[]){"cat", NULL};
//     cmd.redirection = &redir_in;

//     // Appliquer les redirections et exécuter
//     printf("\nTest COMBO REDIR avec la commande : cat < input_test_file > output_test_file\n");
//     apply_redirections(cmd.redirection);
//     execvp(cmd.value, cmd.argv);

//     return 0;
// }

// // TEST HEREDOC IN OK
// int main(void)
// {
//     t_redirection redir_heredoc, redir_in;

//     // Préparer le fichier input_file
//     system("echo 'Input file content' > input_file");

//     // Initialisation des redirections
//     ft_bzero(&redir_heredoc, sizeof(t_redirection));
//     redir_heredoc.type = REDIR_HEREDOC;
//     redir_heredoc.file_name = "EOF";
//     redir_heredoc.next = &redir_in;

//     ft_bzero(&redir_in, sizeof(t_redirection));
//     redir_in.type = REDIR_IN;
//     redir_in.file_name = "input_file";
//     redir_in.next = NULL;

//     // Appliquer les redirections
//     apply_redirections(&redir_heredoc);

//     return 0;
// }

// // TEST HEREDOC OUT OK

// int main(void)
// {
//     t_redirection redir_heredoc, redir_out;
//     t_cmd cmd;

//     // Initialisation des redirections
//     ft_bzero(&redir_heredoc, sizeof(t_redirection));
//     redir_heredoc.type = REDIR_HEREDOC;
//     redir_heredoc.file_name = "EOF";
//     redir_heredoc.next = &redir_out;

//     ft_bzero(&redir_out, sizeof(t_redirection));
//     redir_out.type = REDIR_OUT;
//     redir_out.file_name = "output_file";
//     redir_out.next = NULL;

//     // Initialisation de la commande
//     ft_bzero(&cmd, sizeof(t_cmd));
//     cmd.value = "cat";
//     cmd.argv = (char *[]){"cat", NULL};
//     cmd.redirection = &redir_heredoc;

//     // Appliquer les redirections et exécuter la commande
//     printf("\nTest : cat << EOF > output_file\n");
//     apply_redirections(cmd.redirection);
//     execvp(cmd.value, cmd.argv);

//     return 0;
// }

// // TEST IN OUT
// int main(void)
// {
//     t_redirection redir_in, redir_out;
//     t_cmd cmd;

//     // Préparer les fichiers
//     system("echo 'Input file content' > input_file");

//     // Initialisation des redirections
//     ft_bzero(&redir_in, sizeof(t_redirection));
//     redir_in.type = REDIR_IN;
//     redir_in.file_name = "input_file";
//     redir_in.next = &redir_out;

//     ft_bzero(&redir_out, sizeof(t_redirection));
//     redir_out.type = REDIR_OUT;
//     redir_out.file_name = "output_file";
//     redir_out.next = NULL;

//     // Initialisation de la commande
//     ft_bzero(&cmd, sizeof(t_cmd));
//     cmd.value = "cat";
//     cmd.argv = (char *[]){"cat", NULL};
//     cmd.redirection = &redir_in;

//     // Appliquer les redirections et exécuter la commande
//     printf("\nTest : cat < input_file > output_file\n");
//     apply_redirections(cmd.redirection);
//     execvp(cmd.value, cmd.argv);

//     return 0;
// }

// // TEST HEREDOC APPEND OK
// int main(void)
// {
//     t_redirection redir_heredoc, redir_append;
//     t_cmd cmd;

//     // Préparer le fichier append_file
//     system("echo 'Contenu initial' > append_file");

//     // Initialisation des redirections
//     ft_bzero(&redir_heredoc, sizeof(t_redirection));
//     redir_heredoc.type = REDIR_HEREDOC;
//     redir_heredoc.file_name = "EOF";
//     redir_heredoc.next = &redir_append;

//     ft_bzero(&redir_append, sizeof(t_redirection));
//     redir_append.type = REDIR_APPEND;
//     redir_append.file_name = "append_file";
//     redir_append.next = NULL;

//     // Initialisation de la commande
//     ft_bzero(&cmd, sizeof(t_cmd));
//     cmd.value = "cat";
//     cmd.argv = (char *[]){"cat", NULL};
//     cmd.redirection = &redir_heredoc;

//     // Appliquer les redirections et exécuter la commande
//     printf("\nTest : cat << EOF >> append_file\n");
//     apply_redirections(cmd.redirection);
//     execvp(cmd.value, cmd.argv);

//     return 0;
// }

// // TEST HEREDOC IN OUT OK
// int main(void)
// {
//     t_redirection redir_heredoc, redir_in, redir_out;
//     t_cmd cmd;

//     // Préparer les fichiers
//     system("echo 'Input file content' > input_file");

//     // Initialisation des redirections
//     ft_bzero(&redir_heredoc, sizeof(t_redirection));
//     redir_heredoc.type = REDIR_HEREDOC;
//     redir_heredoc.file_name = "EOF";
//     redir_heredoc.next = &redir_in;

//     ft_bzero(&redir_in, sizeof(t_redirection));
//     redir_in.type = REDIR_IN;
//     redir_in.file_name = "input_file";
//     redir_in.next = &redir_out;

//     ft_bzero(&redir_out, sizeof(t_redirection));
//     redir_out.type = REDIR_OUT;
//     redir_out.file_name = "output_file";
//     redir_out.next = NULL;

//     // Initialisation de la commande
//     ft_bzero(&cmd, sizeof(t_cmd));
//     cmd.value = "cat";
//     cmd.argv = (char *[]){"cat", NULL};
//     cmd.redirection = &redir_heredoc;

//     // Appliquer les redirections et exécuter la commande
//     printf("\nTest : cat << EOF < input_file > output_file\n");
//     apply_redirections(cmd.redirection);
//     execvp(cmd.value, cmd.argv);

//     return 0;
// }

// // TEST MULTIPLE cat < input1.txt < input2.txt > output1.txt OK

// int main(void)
// {
//     t_cmd cmd;
//     t_redirection redir1, redir2, redir3;
//     pid_t pid;
//     int status;

//     // ========== TEST: MULTIPLES REDIRECTIONS ==========
//     printf("\n=== Test MULTIPLES REDIRECTIONS ===\n");

//     // Création des fichiers pour tester l'entrée et la sortie
//     system("echo 'First input file' > input1.txt");
//     system("echo 'Second input file' > input2.txt");
//     system("echo 'Initial output' > output1.txt");
//     system("echo 'Initial output' > output2.txt");

//     // Initialisation de la première redirection d'entrée (<)
//     ft_bzero(&redir1, sizeof(t_redirection));
//     redir1.type = REDIR_IN;
//     redir1.file_name = "input1.txt";
//     redir1.next = &redir2;

//     // Deuxième redirection d'entrée (<) - Doit écraser la première
//     ft_bzero(&redir2, sizeof(t_redirection));
//     redir2.type = REDIR_IN;
//     redir2.file_name = "input2.txt";
//     redir2.next = &redir3;

//     // Redirection de sortie (>) - La deuxième doit écraser la première
//     ft_bzero(&redir3, sizeof(t_redirection));
//     redir3.type = REDIR_OUT;
//     redir3.file_name = "output1.txt";
//     redir3.next = NULL;

//     // Initialisation de la commande
//     ft_bzero(&cmd, sizeof(t_cmd));
//     cmd.value = "cat";
//     cmd.argv = (char *[]){"cat", NULL};
//     cmd.redirection = &redir1;

//     // Exécution avec redirections appliquées
//     pid = fork();
//     if (pid == 0)
//     {
//         apply_redirections(cmd.redirection);
//         execvp(cmd.value, cmd.argv);
//         perror("execvp failed");
//         exit(1);
//     }
//     else
//     {
//         waitpid(pid, &status, 0);
//     }

//     // Vérification du fichier de sortie
//     printf("Contenu final de output1.txt (devrait être 'Second input file') :\n");
//     system("cat output1.txt");

//     return 0;
// }

// //TEST Multiple heredoc OK
// int main(void) {
//     t_redirection redir_heredoc1, redir_heredoc2, redir_in, redir_out;
//     t_cmd cmd;

//     // Vérifier et créer input.txt
//     system("echo 'Contenu de input.txt' > input.txt");
//     if (access("input.txt", F_OK) == -1)
//     {
//         perror("Erreur: input.txt introuvable");
//         return 1;
//     }

//     // Initialisation des redirections
//     ft_bzero(&redir_heredoc1, sizeof(t_redirection));
//     redir_heredoc1.type = REDIR_HEREDOC;
//     redir_heredoc1.file_name = "HEREDOC1";
//     redir_heredoc1.next = &redir_heredoc2;

//     ft_bzero(&redir_heredoc2, sizeof(t_redirection));
//     redir_heredoc2.type = REDIR_HEREDOC;
//     redir_heredoc2.file_name = "HEREDOC2";
//     redir_heredoc2.next = &redir_in;

//     ft_bzero(&redir_in, sizeof(t_redirection));
//     redir_in.type = REDIR_IN;
//     redir_in.file_name = "input.txt";
//     redir_in.next = &redir_out;

//     ft_bzero(&redir_out, sizeof(t_redirection));
//     redir_out.type = REDIR_OUT;
//     redir_out.file_name = "output.txt";
//     redir_out.next = NULL;

//     // Initialisation de la commande
//     ft_bzero(&cmd, sizeof(t_cmd));
//     cmd.value = "cat";
//     cmd.argv = (char *[]){"cat", NULL};
//     cmd.redirection = &redir_heredoc1;

//     // Debug : Affichage des redirections avant exécution
//     printf("\nTest : cat << HEREDOC1 << HEREDOC2 < input.txt > output.txt\n");

//     // Appliquer les redirections et exécuter la commande
//     apply_redirections(cmd.redirection);
    
//     // Vérifier si les fichiers existent après les redirections
//     if (access("input.txt", F_OK) == -1)
//         perror("Erreur après redirections: input.txt supprimé ?");
//     char buffer[1024];
// ssize_t bytes_read;
// while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1)) > 0)
// {
//     buffer[bytes_read] = '\0';
//     printf("DEBUG STDIN : %s\n", buffer);
// }

//     execvp(cmd.value, cmd.argv);

//     // Supprimer le fichier temporaire heredoc après exécution
//     unlink(".heredoc_tmp");

//     // En cas d'erreur
//     perror("execvp failed");
//     return 1;
// }

// //TEST multiple OK

// int main(void)
// {
//     t_redirection redir_heredoc1, redir_heredoc2, redir_in1, redir_in2, redir_out1, redir_out2;
//     t_cmd cmd;

//     // Création des fichiers de test
//     system("echo 'Contenu de in.txt' > in.txt");
//     system("echo 'Contenu de in2.txt' > in2.txt");

//     // Initialisation des redirections
//     ft_bzero(&redir_heredoc1, sizeof(t_redirection));
//     redir_heredoc1.type = REDIR_HEREDOC;
//     redir_heredoc1.file_name = "HEREDOC1";
//     redir_heredoc1.next = &redir_heredoc2;

//     ft_bzero(&redir_heredoc2, sizeof(t_redirection));
//     redir_heredoc2.type = REDIR_HEREDOC;
//     redir_heredoc2.file_name = "HEREDOC2";
//     redir_heredoc2.next = &redir_in1;

//     ft_bzero(&redir_in1, sizeof(t_redirection));
//     redir_in1.type = REDIR_IN;
//     redir_in1.file_name = "in.txt";
//     redir_in1.next = &redir_in2;

//     ft_bzero(&redir_in2, sizeof(t_redirection));
//     redir_in2.type = REDIR_IN;
//     redir_in2.file_name = "in2.txt";
//     redir_in2.next = &redir_out1;

//     ft_bzero(&redir_out1, sizeof(t_redirection));
//     redir_out1.type = REDIR_OUT;
//     redir_out1.file_name = "out.txt";
//     redir_out1.next = &redir_out2;

//     ft_bzero(&redir_out2, sizeof(t_redirection));
//     redir_out2.type = REDIR_OUT;
//     redir_out2.file_name = "out2.txt";
//     redir_out2.next = NULL;

//     // Initialisation de la commande
//     ft_bzero(&cmd, sizeof(t_cmd));
//     cmd.value = "cat";
//     cmd.argv = (char *[]){"cat", NULL};
//     cmd.redirection = &redir_heredoc1;

//     // Exécution avec redirections appliquées
//     printf("\nTest : cat << HEREDOC1 << HEREDOC2 < in.txt < in2.txt > out.txt > out2.txt\n");
//     apply_redirections(cmd.redirection);
//     execvp(cmd.value, cmd.argv);

//     // En cas d'erreur
//     perror("execvp failed");
//     return 1;
// }

// int main(void) //cat << HEREDOC1 << HEREDOC2 < in.txt < in2.txt > out.txt > out2.txt OK
// {
//     t_redirection redir_heredoc1, redir_heredoc2, redir_in1, redir_in2, redir_out1, redir_out2;
//     t_cmd cmd;

//     // Création des fichiers de test
//     system("echo 'Contenu de in.txt' > in.txt");
//     system("echo 'Contenu de in2.txt' > in2.txt");

//     // Initialisation des redirections
//     ft_bzero(&redir_heredoc1, sizeof(t_redirection));
//     redir_heredoc1.type = REDIR_HEREDOC;
//     redir_heredoc1.file_name = "HEREDOC1";
//     redir_heredoc1.next = &redir_heredoc2;

//     ft_bzero(&redir_heredoc2, sizeof(t_redirection));
//     redir_heredoc2.type = REDIR_HEREDOC;
//     redir_heredoc2.file_name = "HEREDOC2";
//     redir_heredoc2.next = &redir_in1;

//     ft_bzero(&redir_in1, sizeof(t_redirection));
//     redir_in1.type = REDIR_IN;
//     redir_in1.file_name = "in.txt";
//     redir_in1.next = &redir_in2;

//     ft_bzero(&redir_in2, sizeof(t_redirection));
//     redir_in2.type = REDIR_IN;
//     redir_in2.file_name = "in2.txt";
//     redir_in2.next = &redir_out1;

//     ft_bzero(&redir_out1, sizeof(t_redirection));
//     redir_out1.type = REDIR_OUT;
//     redir_out1.file_name = "out.txt";
//     redir_out1.next = &redir_out2;

//     ft_bzero(&redir_out2, sizeof(t_redirection));
//     redir_out2.type = REDIR_OUT;
//     redir_out2.file_name = "out2.txt";
//     redir_out2.next = NULL;

//     // Initialisation de la commande
//     ft_bzero(&cmd, sizeof(t_cmd));
//     cmd.value = "cat";
//     cmd.argv = (char *[]){"cat", NULL};
//     cmd.redirection = &redir_heredoc1;

//     // Exécution avec redirections appliquées
//     apply_redirections(cmd.redirection);
//     execvp(cmd.value, cmd.argv);

//     perror("execvp failed");
//     return 1;
// }

// //Test fichier inexistant, CTRL C normal a faire dans cas main de test

// int main(void)
// {
//     t_redirection redir_in;
//     t_cmd cmd;

//     // Initialisation de la redirection d'entrée
//     ft_bzero(&redir_in, sizeof(t_redirection));
//     redir_in.type = REDIR_IN;
//     redir_in.file_name = "fichier_inexistant.txt";
//     redir_in.next = NULL;

//     // Initialisation de la commande
//     ft_bzero(&cmd, sizeof(t_cmd));
//     cmd.value = "cat";
//     cmd.argv = (char *[]){"cat", NULL};
//     cmd.redirection = &redir_in;

//     // Exécution avec redirections appliquées
//     apply_redirections(cmd.redirection);
//     execvp(cmd.value, cmd.argv);

//     perror("execvp failed");
//     return 1;
// }


// TEST Verification de la fermeture des fd et du unlink apres execution
// int main(int argc, char **argv, char **envp) 
// {
//     t_data data;
//     t_cmd cmd;
//     t_redirection heredoc_redir;

//     (void)argc;
//     (void)argv;

//     // Initialiser la redirection heredoc
//     heredoc_redir.file_name = strdup(".heredoc_tmp"); // Laisser le shell le créer
//     heredoc_redir.type = REDIR_HEREDOC;
//     heredoc_redir.next = NULL;

//     // Initialiser la commande (simule `echo hello << EOF`)
//     cmd.value = strdup("echo");
//     cmd.argv = (char *[]){"echo", "hello", NULL};
//     cmd.argc = 2;
//     cmd.redirection = &heredoc_redir;
//     cmd.next = NULL;

//     // Initialiser `t_data`
//     data.cmd_lst = &cmd;
//     data.lst_exit = 0;

//     // 🔹 Vérifier les fichiers ouverts AVANT `executer()`
//     printf("\n🛠️ Vérification des fichiers ouverts DANS MINISHELL AVANT `executer()`...\n");
//     char cmd_check_before[128];
//     sprintf(cmd_check_before, "ls -l /proc/%d/fd | grep .heredoc_tmp", getpid());
//     system(cmd_check_before);

//     // Exécuter la commande (cela passera par `executer() → exec_simple_builtin_heredoc()`)
//     printf("\n=== Début du test ===\n");
//     executer(&data, envp);
//     printf("\n=== Fin du test ===\n");

//     // 🔹 Vérifier les fichiers ouverts APRES `executer()`
//     printf("\n🛠️ Vérification des fichiers ouverts DANS MINISHELL APRES `executer()`...\n");
//     char cmd_check_after[128];
//     sprintf(cmd_check_after, "ls -l /proc/%d/fd | grep .heredoc_tmp", getpid());
//     system(cmd_check_after);

//     // 🔹 Vérifier si `.heredoc_tmp` existe encore après `close_redirections()`
//     if (access(".heredoc_tmp", F_OK) == 0)
//     {
//         printf("❌ `.heredoc_tmp` existe encore sur le disque après `close_redirections()`\n");
//         // 🔹 Essayer de le supprimer
//         if (unlink(".heredoc_tmp") == 0)
//             printf("✅ Suppression manuelle de `.heredoc_tmp` après fermeture.\n");
//         else
//             perror("❌ Impossible de supprimer `.heredoc_tmp` après `close_redirections()`");
//     }
//     else
//         printf("✅ `.heredoc_tmp` a été supprimé avec succès après `close_redirections()`\n");

//     // Nettoyage mémoire
//     free(cmd.value);
//     free(heredoc_redir.file_name);

//     return 0;
// }


// int main(int argc, char **argv, char **envp) {
//     t_data data;
//     t_cmd cmd;
//     t_varenv *env_list;
//     t_redirection redir1, redir2, redir3;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation de l'environnement
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Configuration des redirections heredoc (`<< EOF << EOF << EOF`)
//     redir1.type = REDIR_HEREDOC;
//     redir1.file_name = strdup("EOF");
//     redir1.next = &redir2;

//     redir2.type = REDIR_HEREDOC;
//     redir2.file_name = strdup("EOF");
//     redir2.next = &redir3;

//     redir3.type = REDIR_HEREDOC;
//     redir3.file_name = strdup("EOF");
//     redir3.next = NULL;

//     // 🔹 Commande `echo << EOF << EOF << EOF`
//     cmd.value = strdup("echo");
// cmd.argv = (char *[]){"echo", "test", NULL};
//     cmd.argc = 1;
//     cmd.redirection = &redir1;
//     cmd.next = NULL;

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd;
//     data.lst_exit = 0;

//     // 🔹 Exécution via `executer()` pour tester `handle_heredocs_simple_cmd()`
//     printf("\n🔽🔽🔽 DÉBUT DU TEST MULTIPLES HEREDOCS AVEC BUILTIN 🔽🔽🔽\n");
//     printf("▶ Exécution de `echo << EOF << EOF << EOF`\n");
//     printf("----------------------------------------------------\n");

//     executer(&data, envp);  // 🔹 Appel direct à `executer()` -> `handle_heredocs_simple_cmd()` doit tout gérer

//     printf("----------------------------------------------------\n");
//     printf("🔼🔼🔼 FIN DU TEST 🔼🔼🔼\n");

//     // 🔹 Nettoyage mémoire
//     free(cmd.value);
//     free(redir1.file_name);
//     free(redir2.file_name);
//     free(redir3.file_name);
//     free_varenv(data.varenv_lst);

//     return 0;
// }

// int main(int argc, char **argv, char **envp) {
//     t_data data;
//     t_cmd cmd;
//     t_varenv *env_list;
//     t_redirection redir1, redir2, redir3;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation de l'environnement
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Configuration des redirections heredoc (`<< EOF << EOF << EOF`)
//     redir1.type = REDIR_HEREDOC;
//     redir1.file_name = strdup("EOF");
//     redir1.next = &redir2;

//     redir2.type = REDIR_HEREDOC;
//     redir2.file_name = strdup("EOF");
//     redir2.next = &redir3;

//     redir3.type = REDIR_HEREDOC;
//     redir3.file_name = strdup("EOF");
//     redir3.next = NULL;

//     // 🔹 Commande `cat << EOF << EOF << EOF`
//     cmd.value = strdup("cat");
//     cmd.argv = (char *[]){"cat", NULL};
//     cmd.argc = 1;
//     cmd.redirection = &redir1;
//     cmd.next = NULL;

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd;
//     data.lst_exit = 0;

//     // 🔹 Exécution via `executer()` pour tester `handle_heredocs_simple_cmd()`
//     printf("\n🔽🔽🔽 DÉBUT DU TEST MULTIPLES HEREDOCS 🔽🔽🔽\n");
//     printf("▶ Exécution de `cat << EOF << EOF << EOF`\n");
//     printf("----------------------------------------------------\n");

//     executer(&data, envp);  // 🔹 Appel direct à `executer()` -> `handle_heredocs_simple_cmd()` doit tout gérer

//     printf("----------------------------------------------------\n");
//     printf("🔼🔼🔼 FIN DU TEST 🔼🔼🔼\n");

//     // 🔹 Nettoyage mémoire
//     free(cmd.value);
//     free(redir1.file_name);
//     free(redir2.file_name);
//     free(redir3.file_name);
//     free_varenv(data.varenv_lst);

//     return 0;
// }
