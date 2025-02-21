// //Trouver le path
// int main(int argc, char **argv, char **envp)
// {
//     t_varenv *env_list;
//     char *cmd_path;

//     (void)argv;
//     (void)argc;

//     // 🔹 Initialisation de l'environnement
//     env_list = init_varenv(envp);
    
//     // 🔹 Tester `find_cmd_path()`
//     cmd_path = find_cmd_path("ls", env_list);
//     if (!cmd_path)
//         printf("❌ `find_cmd_path()` n'a pas trouvé `ls`\n");
//     else
//         printf("✅ `find_cmd_path()` a trouvé : %s\n", cmd_path);

//     return 0;
// }

////Test execution externe
// int main(int argc, char **argv, char **envp)
// {
//     t_data data;
//     t_cmd cmd;
//     t_varenv *env_list;
    
//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation d'un environnement minimaliste
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Initialisation de la commande (exécute `ls -l`)
//     cmd.value = strdup("ls");
//     cmd.argv = (char *[]){"ls", "-l", NULL};
//     cmd.argc = 2;
//     cmd.redirection = NULL;  // Pas de redirection
//     cmd.next = NULL;

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd;
//     data.lst_exit = 0;

//     // 🔹 Lancement du test
//     printf("\n🛠️ Test de `exec_simple_extern_cmd()` via `executer()`...\n");
//     executer(&data, envp);
//     printf("\n✅ Test terminé !\n");

//     // 🔹 Vérification de la suppression du fichier `.heredoc_tmp`
//     if (access(".heredoc_tmp", F_OK) == 0)
//     {
//         printf("❌ `.heredoc_tmp` existe encore après exécution, problème potentiel.\n");
//         if (unlink(".heredoc_tmp") == 0)
//             printf("✅ Suppression manuelle de `.heredoc_tmp` après test.\n");
//         else
//             perror("❌ Impossible de supprimer `.heredoc_tmp`");
//     }
//     else
//         printf("✅ `.heredoc_tmp` a été supprimé correctement après exécution.\n");

//     // 🔹 Nettoyage mémoire
//     free(cmd.value);
//     return 0;
// }

//TEST ls -l | cat | wc -l (retourne 23)
// int main(int argc, char **argv, char **envp)
// {
//     t_data data;
//     t_cmd cmd1, cmd2, cmd3;
//     t_varenv *env_list;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation d'un environnement minimaliste
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Initialisation des commandes du pipeline : `ls -l | cat | wc -l`
    
//     // Commande 1 : `ls -l`
//     cmd1.value = strdup("ls");
//     cmd1.argv = (char *[]){"ls", "-l", NULL};
//     cmd1.argc = 2;
//     cmd1.redirection = NULL;  
//     cmd1.next = &cmd2;  // Lien vers la prochaine commande

//     // Commande 2 : `cat`
//     cmd2.value = strdup("cat");
//     cmd2.argv = (char *[]){"cat", NULL};
//     cmd2.argc = 1;
//     cmd2.redirection = NULL;  
//     cmd2.next = &cmd3;  // Lien vers la prochaine commande

//     // Commande 3 : `wc -l`
//     cmd3.value = strdup("wc");
//     cmd3.argv = (char *[]){"wc", "-l", NULL};
//     cmd3.argc = 2;
//     cmd3.redirection = NULL;  
//     cmd3.next = NULL;  // Dernière commande du pipeline

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd1;
//     data.lst_exit = 0;

//     // 🔹 Lancement du test
//     printf("\n🔽🔽🔽 DÉBUT DU TEST PIPELINE 🔽🔽🔽\n");
//     printf("▶ Exécution du pipeline : ls -l | cat | wc -l\n");
//     printf("----------------------------------------------------\n");

//     executer(&data, envp);  // 🔹 Exécuter les commandes

//     printf("----------------------------------------------------\n");
//     printf("🔼🔼🔼 FIN DU TEST PIPELINE 🔼🔼🔼\n");

//     // 🔹 Nettoyage mémoire
//     free(cmd1.value);
//     free(cmd2.value);
//     free(cmd3.value);
//     free_varenv(data.varenv_lst);

//     return 0;
// }

// // TEST echo "Hello World" | tr ' ' '_' | rev
// int main(int argc, char **argv, char **envp)
// {
//     t_data data;
//     t_cmd cmd1, cmd2, cmd3;
//     t_varenv *env_list;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation d'un environnement minimaliste
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Initialisation des commandes du pipeline : `echo "Hello World" | tr ' ' '_' | rev`
    
//     // Commande 1 : `echo "Hello World"`
//     cmd1.value = strdup("echo");
//     cmd1.argv = (char *[]){"echo", "Hello World", NULL};
//     cmd1.argc = 2;
//     cmd1.redirection = NULL;  
//     cmd1.next = &cmd2;  // Lien vers la prochaine commande

//     // Commande 2 : `tr ' ' '_'`
//     cmd2.value = strdup("tr");
//     cmd2.argv = (char *[]){"tr", " ", "_", NULL};
//     cmd2.argc = 3;
//     cmd2.redirection = NULL;  
//     cmd2.next = &cmd3;  // Lien vers la prochaine commande

//     // Commande 3 : `rev`
//     cmd3.value = strdup("rev");
//     cmd3.argv = (char *[]){"rev", NULL};
//     cmd3.argc = 1;
//     cmd3.redirection = NULL;  
//     cmd3.next = NULL;  // Dernière commande du pipeline

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd1;
//     data.lst_exit = 0;

//     // 🔹 Lancement du test
//     printf("\n🔽🔽🔽 DÉBUT DU TEST PIPELINE 🔽🔽🔽\n");
//     printf("▶ Exécution du pipeline : echo \"Hello World\" | tr ' ' '_' | rev\n");
//     printf("----------------------------------------------------\n");

//     executer(&data, envp);  // 🔹 Exécuter les commandes

//     printf("----------------------------------------------------\n");
//     printf("🔼🔼🔼 FIN DU TEST PIPELINE 🔼🔼🔼\n");

//     // 🔹 Nettoyage mémoire
//     free(cmd1.value);
//     free(cmd2.value);
//     free(cmd3.value);
//     free_varenv(data.varenv_lst);
//     return 0;
// }



// // TEST echo "Hello Minishell" | tr ' ' '_' > output.txt

// int main(int argc, char **argv, char **envp)
// {
//     t_data data;
//     t_cmd cmd1, cmd2;
//     t_varenv *env_list;
//     t_redirection redir;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation d'un environnement minimaliste
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Configuration de la redirection `>`
//     redir.type = REDIR_OUT;
//     redir.file_name = strdup("output.txt");
//     redir.next = NULL;

//     // 🔹 Initialisation des commandes du pipeline : `echo "Hello Minishell" | tr ' ' '_' > output.txt`
    
//     // Commande 1 : `echo "Hello Minishell"`
//     cmd1.value = strdup("echo");
//     cmd1.argv = (char *[]){"echo", "Hello Minishell", NULL};
//     cmd1.argc = 2;
//     cmd1.redirection = NULL;
//     cmd1.next = &cmd2;  // Lien vers la prochaine commande

//     // Commande 2 : `tr ' ' '_'`
//     cmd2.value = strdup("tr");
//     cmd2.argv = (char *[]){"tr", " ", "_", NULL};
//     cmd2.argc = 3;
//     cmd2.redirection = &redir;  // 🔹 Ajout de la redirection ici
//     cmd2.next = NULL;  // Dernière commande du pipeline

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd1;
//     data.lst_exit = 0;

//     // 🔹 Lancement du test
//     printf("\n🔽🔽🔽 DÉBUT DU TEST PIPELINE 🔽🔽🔽\n");
//     printf("▶ Exécution du pipeline : echo \"Hello Minishell\" | tr ' ' '_' > output.txt\n");
//     printf("----------------------------------------------------\n");

//     executer(&data, envp);  // 🔹 Exécuter les commandes

//     printf("----------------------------------------------------\n");
//     printf("🔼🔼🔼 FIN DU TEST PIPELINE 🔼🔼🔼\n");

//     // 🔹 Vérification du contenu du fichier `output.txt`
//     printf("\n📂 Contenu du fichier `output.txt` :\n");
//     system("cat output.txt");

//     // 🔹 Nettoyage mémoire
//     free(cmd1.value);
//     free(cmd2.value);
//     free(redir.file_name);
//     free_varenv(data.varenv_lst);

//     return 0;
// }

// int main(int argc, char **argv, char **envp)
// {
//     t_data data;
//     t_cmd cmd1, cmd2, cmd3, cmd4;
//     t_varenv *env_list;
//     t_redirection redir1, redir2;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation d'un environnement minimaliste
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Configuration du premier heredoc (`<< A`)
//     redir1.type = REDIR_HEREDOC;
//     redir1.file_name = strdup(".heredoc_A");  // Fichier temporaire pour heredoc A
//     redir1.next = NULL;

//     // 🔹 Configuration du deuxième heredoc (`<< B`)
//     redir2.type = REDIR_HEREDOC;
//     redir2.file_name = strdup(".heredoc_B");  // Fichier temporaire pour heredoc B
//     redir2.next = NULL;

//     // Écriture du premier heredoc (`A`)
//     int fd = open(".heredoc_A", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd == -1)
//     {
//         perror("Erreur lors de la création du fichier heredoc A");
//         return 1;
//     }
//     write(fd, "hello minishell\n", 16);
//     close(fd);

//     // Écriture du deuxième heredoc (`B`)
//     fd = open(".heredoc_B", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd == -1)
//     {
//         perror("Erreur lors de la création du fichier heredoc B");
//         return 1;
//     }
//     write(fd, "cool feature\n", 13);
//     close(fd);

//     // 🔹 Commande 1 : `cat < .heredoc_A`
//     cmd1.value = strdup("cat");
//     cmd1.argv = (char *[]){"cat", NULL};
//     cmd1.argc = 1;
//     cmd1.redirection = &redir1;  // Associer le premier heredoc
//     cmd1.next = &cmd2;  // Lien vers la prochaine commande

//     // 🔹 Commande 2 : `tr 'a-z' 'A-Z'`
//     cmd2.value = strdup("tr");
//     cmd2.argv = (char *[]){"tr", "a-z", "A-Z", NULL};
//     cmd2.argc = 3;
//     cmd2.redirection = NULL;
//     cmd2.next = &cmd3;  // Lien vers la prochaine commande

//     // 🔹 Commande 3 : `cat < .heredoc_B`
//     cmd3.value = strdup("cat");
//     cmd3.argv = (char *[]){"cat", NULL};
//     cmd3.argc = 1;
//     cmd3.redirection = &redir2;  // Associer le deuxième heredoc
//     cmd3.next = &cmd4;  // Lien vers la prochaine commande

//     // 🔹 Commande 4 : `rev`
//     cmd4.value = strdup("rev");
//     cmd4.argv = (char *[]){"rev", NULL};
//     cmd4.argc = 1;
//     cmd4.redirection = NULL;
//     cmd4.next = NULL;  // Dernière commande du pipeline

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd1;
//     data.lst_exit = 0;

//     // 🔹 Lancement du test
//     printf("\n🔽🔽🔽 DÉBUT DU TEST PIPELINE + MULTIPLES HEREDOC 🔽🔽🔽\n");
//     printf("▶ Exécution du pipeline : cat << A | tr 'a-z' 'A-Z' | cat << B | rev\n");
//     printf("----------------------------------------------------\n");

//     executer(&data, envp);  // 🔹 Exécuter les commandes

//     printf("----------------------------------------------------\n");
//     printf("🔼🔼🔼 FIN DU TEST PIPELINE 🔼🔼🔼\n");

//     // 🔹 Nettoyage mémoire
//     free(cmd1.value);
//     free(cmd2.value);
//     free(cmd3.value);
//     free(cmd4.value);
//     free(redir1.file_name);
//     free(redir2.file_name);
//     free_varenv(data.varenv_lst);

//     // 🔹 Supprimer les fichiers temporaires des heredocs
//     unlink(".heredoc_A");
//     unlink(".heredoc_B");

//     return 0;
// }

// Test PIPELINE heredoc COntenu heredoc a l'envers
// int main(int argc, char **argv, char **envp)
// {
//     t_data data;
//     t_cmd cmd1, cmd2, cmd3;
//     t_varenv *env_list;
//     t_redirection redir;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation d'un environnement minimaliste
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Configuration du heredoc (`<<`)
//     redir.type = REDIR_HEREDOC;
//     redir.file_name = strdup(".heredoc_tmp");  // Fichier temporaire
//     redir.next = NULL;

//     // Écriture manuelle du contenu du heredoc dans le fichier temporaire
//     int fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd == -1)
//     {
//         perror("Erreur lors de la création du fichier heredoc");
//         return 1;
//     }
//     write(fd, "hello minishell\n", 16);
//     close(fd);

//     // 🔹 Commande 1 : `cat < .heredoc_tmp`
//     cmd1.value = strdup("cat");
//     cmd1.argv = (char *[]){"cat", NULL};
//     cmd1.argc = 1;
//     cmd1.redirection = &redir;  // Associer le heredoc
//     cmd1.next = &cmd2;  // Lien vers la prochaine commande

//     // 🔹 Commande 2 : `tr 'a-z' 'A-Z'`
//     cmd2.value = strdup("tr");
//     cmd2.argv = (char *[]){"tr", "a-z", "A-Z", NULL};
//     cmd2.argc = 3;
//     cmd2.redirection = NULL;
//     cmd2.next = &cmd3;  // Lien vers la prochaine commande

//     // 🔹 Commande 3 : `rev`
//     cmd3.value = strdup("rev");
//     cmd3.argv = (char *[]){"rev", NULL};
//     cmd3.argc = 1;
//     cmd3.redirection = NULL;
//     cmd3.next = NULL;  // Dernière commande du pipeline

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd1;
//     data.lst_exit = 0;

//     // 🔹 Lancement du test
//     printf("\n🔽🔽🔽 DÉBUT DU TEST PIPELINE + HEREDOC 🔽🔽🔽\n");
//     printf("▶ Exécution du pipeline : cat << EOF | tr 'a-z' 'A-Z' | rev\n");
//     printf("----------------------------------------------------\n");

//     executer(&data, envp);  // 🔹 Exécuter les commandes

//     printf("----------------------------------------------------\n");
//     printf("🔼🔼🔼 FIN DU TEST PIPELINE 🔼🔼🔼\n");

//     // 🔹 Nettoyage mémoire
//     free(cmd1.value);
//     free(cmd2.value);
//     free(cmd3.value);
//     free(redir.file_name);
//     free_varenv(data.varenv_lst);

//     // 🔹 Supprimer le fichier temporaire `.heredoc_tmp`
//     unlink(".heredoc_tmp");

//     return 0;
// }


// int main(int argc, char **argv, char **envp)
// {
//     t_data data;
//     t_cmd cmd1, cmd2, cmd3;
//     t_varenv *env_list;
//     t_redirection redir1, redir2;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation d'un environnement minimaliste
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Configuration des heredocs (`<< A` et `<< B`)
//     redir1.type = REDIR_HEREDOC;
//     redir1.file_name = strdup(".heredoc_A");  // Fichier temporaire pour heredoc A
//     redir1.next = &redir2;  // Lien vers le prochain heredoc

//     redir2.type = REDIR_HEREDOC;
//     redir2.file_name = strdup(".heredoc_B");  // Fichier temporaire pour heredoc B
//     redir2.next = NULL;  // Dernier heredoc

//     // 🔹 Écriture manuelle des contenus des heredocs
//     int fd = open(".heredoc_A", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd == -1)
//     {
//         perror("Erreur lors de la création du fichier heredoc A");
//         return 1;
//     }
//     write(fd, "premier heredoc\n", 16);
//     close(fd);

//     fd = open(".heredoc_B", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd == -1)
//     {
//         perror("Erreur lors de la création du fichier heredoc B");
//         return 1;
//     }
//     write(fd, "deuxieme heredoc\n", 17);
//     close(fd);

//     // 🔹 Commande 1 : `cat << A << B`
//     cmd1.value = strdup("cat");
//     cmd1.argv = (char *[]){"cat", NULL};
//     cmd1.argc = 1;
//     cmd1.redirection = &redir1;  // Associer les deux heredocs
//     cmd1.next = &cmd2;  // Lien vers la prochaine commande

//     // 🔹 Commande 2 : `tr 'a-z' 'A-Z'`
//     cmd2.value = strdup("tr");
//     cmd2.argv = (char *[]){"tr", "a-z", "A-Z", NULL};
//     cmd2.argc = 3;
//     cmd2.redirection = NULL;
//     cmd2.next = &cmd3;  // Lien vers la prochaine commande

//     // 🔹 Commande 3 : `rev`
//     cmd3.value = strdup("rev");
//     cmd3.argv = (char *[]){"rev", NULL};
//     cmd3.argc = 1;
//     cmd3.redirection = NULL;
//     cmd3.next = NULL;  // Dernière commande du pipeline

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd1;
//     data.lst_exit = 0;

//     // 🔹 Lancement du test
//     printf("\n🔽🔽🔽 DÉBUT DU TEST PIPELINE + MULTIPLES HEREDOC DANS UNE COMMANDE 🔽🔽🔽\n");
//     printf("▶ Exécution du pipeline : cat << A << B | tr 'a-z' 'A-Z' | rev\n");
//     printf("----------------------------------------------------\n");

//     executer(&data, envp);  // 🔹 Exécuter les commandes

//     printf("----------------------------------------------------\n");
//     printf("🔼🔼🔼 FIN DU TEST PIPELINE 🔼🔼🔼\n");

//     // 🔹 Nettoyage mémoire
//     free(cmd1.value);
//     free(cmd2.value);
//     free(cmd3.value);
//     free(redir1.file_name);
//     free(redir2.file_name);
//     free_varenv(data.varenv_lst);

//     // 🔹 Suppression des fichiers temporaires des heredocs
//     unlink(".heredoc_A");
//     unlink(".heredoc_B");

//     return 0;
// }


// int main(int argc, char **argv, char **envp)
// {
//     t_data data;
//     t_cmd cmd1, cmd2, cmd3;
//     t_varenv *env_list;
//     t_redirection redir_A, redir_B, redir_C, redir_D, redir_E;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation d'un environnement minimaliste
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Configuration des heredocs (`<< A << B << C << D << E`)
//     redir_A.type = REDIR_HEREDOC;
//     redir_A.file_name = strdup("HA");
//     redir_A.next = &redir_B;

//     redir_B.type = REDIR_HEREDOC;
//     redir_B.file_name = strdup("HB");
//     redir_B.next = &redir_C;

//     redir_C.type = REDIR_HEREDOC;
//     redir_C.file_name = strdup("HC");
//     redir_C.next = &redir_D;

//     redir_D.type = REDIR_HEREDOC;
//     redir_D.file_name = strdup("HD");
//     redir_D.next = &redir_E;

//     redir_E.type = REDIR_HEREDOC;
//     redir_E.file_name = strdup("HE"); // Le dernier heredoc utilisé
//     redir_E.next = NULL;

//     // 🔹 Écriture manuelle des contenus des heredocs
//     int fd = open(".heredoc_A", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     write(fd, "Contenu du heredoc A\n", 22);
//     close(fd);

//     fd = open(".heredoc_B", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     write(fd, "Contenu du heredoc B\n", 22);
//     close(fd);

//     fd = open(".heredoc_C", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     write(fd, "Contenu du heredoc C\n", 22);
//     close(fd);

//     fd = open(".heredoc_D", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     write(fd, "Contenu du heredoc D\n", 22);
//     close(fd);

//     fd = open(".heredoc_E", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     write(fd, "Contenu du heredoc E\n", 22);
//     close(fd);

//     // 🔹 Commande 1 : `cat << A << B << C << D << E`
//     cmd1.value = strdup("cat");
//     cmd1.argv = (char *[]){"cat", NULL};
//     cmd1.argc = 1;
//     cmd1.redirection = &redir_A;  // Associer les cinq heredocs
//     cmd1.next = &cmd2;  // Lien vers la prochaine commande

//     // 🔹 Commande 2 : `tr 'a-z' 'A-Z'`
//     cmd2.value = strdup("tr");
//     cmd2.argv = (char *[]){"tr", "a-z", "A-Z", NULL};
//     cmd2.argc = 3;
//     cmd2.redirection = NULL;
//     cmd2.next = &cmd3;  // Lien vers la prochaine commande

//     // 🔹 Commande 3 : `rev`
//     cmd3.value = strdup("rev");
//     cmd3.argv = (char *[]){"rev", NULL};
//     cmd3.argc = 1;
//     cmd3.redirection = NULL;
//     cmd3.next = NULL;  // Dernière commande du pipeline

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd1;
//     data.lst_exit = 0;

//     // 🔹 Lancement du test
//     printf("\n🔽🔽🔽 DÉBUT DU TEST PIPELINE + MULTIPLES HEREDOC 🔽🔽🔽\n");
//     printf("▶ Exécution du pipeline : cat << A << B << C << D << E | tr 'a-z' 'A-Z' | rev\n");
//     printf("----------------------------------------------------\n");

//     executer(&data, envp);  // 🔹 Exécuter les commandes

//     printf("----------------------------------------------------\n");
//     printf("🔼🔼🔼 FIN DU TEST PIPELINE 🔼🔼🔼\n");

//     // 🔹 Nettoyage mémoire
//     free(cmd1.value);
//     free(cmd2.value);
//     free(cmd3.value);
//     free(redir_A.file_name);
//     free(redir_B.file_name);
//     free(redir_C.file_name);
//     free(redir_D.file_name);
//     free(redir_E.file_name);
//     free_varenv(data.varenv_lst);

//     // 🔹 Suppression des fichiers temporaires des heredocs
//     unlink(".heredoc_A");
//     unlink(".heredoc_B");
//     unlink(".heredoc_C");
//     unlink(".heredoc_D");
//     unlink(".heredoc_E");

//     return 0;
// }



// int main(int argc, char **argv, char **envp)
// {
//     t_data data;
//     t_cmd cmd1;
//     t_varenv *env_list;
//     t_redirection redir_A, redir_B, redir_C, redir_D;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation d'un environnement minimaliste
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Configuration des heredocs (`<< A << B << C << D`)
//     redir_A.type = REDIR_HEREDOC;
//     redir_A.file_name = strdup(".heredoc_A");
//     redir_A.next = &redir_B;

//     redir_B.type = REDIR_HEREDOC;
//     redir_B.file_name = strdup(".heredoc_B");
//     redir_B.next = &redir_C;

//     redir_C.type = REDIR_HEREDOC;
//     redir_C.file_name = strdup(".heredoc_C");
//     redir_C.next = &redir_D;

//     redir_D.type = REDIR_HEREDOC;
//     redir_D.file_name = strdup(".heredoc_D"); // Le dernier heredoc utilisé
//     redir_D.next = NULL;

//     // 🔹 Écriture manuelle des contenus des heredocs
//     int fd = open(".heredoc_A", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     write(fd, "Contenu du heredoc A\n", 22);
//     close(fd);

//     fd = open(".heredoc_B", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     write(fd, "Contenu du heredoc B\n", 22);
//     close(fd);

//     fd = open(".heredoc_C", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     write(fd, "Contenu du heredoc C\n", 22);
//     close(fd);

//     fd = open(".heredoc_D", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     write(fd, "Contenu du heredoc D\n", 22);
//     close(fd);

//     // 🔹 Commande : `cat << A << B << C << D`
//     cmd1.value = strdup("cat");
//     cmd1.argv = (char *[]){"cat", NULL};
//     cmd1.argc = 1;
//     cmd1.redirection = &redir_A;  // Associer les quatre heredocs
//     cmd1.next = NULL;  // Pas de pipeline

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd1;
//     data.lst_exit = 0;

//     // 🔹 Lancement du test
//     printf("\n🔽🔽🔽 DÉBUT DU TEST MULTIPLES HEREDOC SANS PIPELINE 🔽🔽🔽\n");
//     printf("▶ Exécution : cat << A << B << C << D\n");
//     printf("----------------------------------------------------\n");

//     executer(&data, envp);  // 🔹 Exécuter la commande

//     printf("----------------------------------------------------\n");
//     printf("🔼🔼🔼 FIN DU TEST MULTIPLES HEREDOC 🔼🔼🔼\n");

//     // 🔹 Nettoyage mémoire
//     free(cmd1.value);
//     free(redir_A.file_name);
//     free(redir_B.file_name);
//     free(redir_C.file_name);
//     free(redir_D.file_name);
//     free_varenv(data.varenv_lst);

//     // 🔹 Suppression des fichiers temporaires des heredocs
//     unlink(".heredoc_A");
//     unlink(".heredoc_B");
//     unlink(".heredoc_C");
//     unlink(".heredoc_D");

//     return 0;
// }

// int main(int argc, char **argv, char **envp) {
//     t_data data;
//     t_cmd cmd1, cmd2, cmd3;
//     t_varenv *env_list;
//     t_redirection redir1_1, redir1_2, redir3_1, redir3_2;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation de l'environnement
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Configuration des heredocs pour la première commande (`cat << EOF1 << EOF2`)
//     redir1_1.type = REDIR_HEREDOC;
//     redir1_1.file_name = strdup("EOF");
//     redir1_1.next = &redir1_2;

//     redir1_2.type = REDIR_HEREDOC;
//     redir1_2.file_name = strdup("EOF");
//     redir1_2.next = NULL;

//     // 🔹 Commande 1 : `cat << EOF1 << EOF2`
//     cmd1.value = strdup("cat");
//     cmd1.argv = (char *[]){"cat", NULL};
//     cmd1.argc = 1;
//     cmd1.redirection = &redir1_1; // Associer les heredocs
//     cmd1.next = &cmd2; // Lien vers la prochaine commande

//     // 🔹 Commande 2 : `tr 'a-z' 'A-Z'`
//     cmd2.value = strdup("tr");
//     cmd2.argv = (char *[]){"tr", "a-z", "A-Z", NULL};
//     cmd2.argc = 3;
//     cmd2.redirection = NULL; // Pas de heredoc ici
//     cmd2.next = &cmd3; // Lien vers la prochaine commande

//     // 🔹 Configuration des heredocs pour la troisième commande (`rev << EOF3 << EOF4`)
//     redir3_1.type = REDIR_HEREDOC;
//     redir3_1.file_name = strdup("EOF");
//     redir3_1.next = &redir3_2;

//     redir3_2.type = REDIR_HEREDOC;
//     redir3_2.file_name = strdup("EOF");
//     redir3_2.next = NULL;

//     // 🔹 Commande 3 : `rev << EOF3 << EOF4`
//     cmd3.value = strdup("rev");
//     cmd3.argv = (char *[]){"rev", NULL};
//     cmd3.argc = 1;
//     cmd3.redirection = &redir3_1; // Associer les heredocs
//     cmd3.next = NULL; // Dernière commande du pipeline

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd1;
//     data.lst_exit = 0;

//     // 🔹 Exécution via `executer()` pour tester `handle_heredocs_pipeline()`
//     printf("\n🔽🔽🔽 DÉBUT DU TEST PIPELINE AVEC HEREDOCS DES DEUX CÔTÉS 🔽🔽🔽\n");
//     printf("▶ Exécution du pipeline : cat << EOF1 << EOF2 | tr 'a-z' 'A-Z' | rev << EOF3 << EOF4\n");
//     printf("----------------------------------------------------\n");

//     executer(&data, envp);  // 🔹 Appel direct à `executer()` -> `handle_heredocs_pipeline()` doit tout gérer

//     printf("----------------------------------------------------\n");
//     printf("🔼🔼🔼 FIN DU TEST 🔼🔼🔼\n");

//     // 🔹 Nettoyage mémoire
//     free(cmd1.value);
//     free(cmd2.value);
//     free(cmd3.value);
//     free(redir1_1.file_name);
//     free(redir1_2.file_name);
//     free(redir3_1.file_name);
//     free(redir3_2.file_name);
//     free_varenv(data.varenv_lst);

//     return 0;
// }


// int main(int argc, char **argv, char **envp) {
//     t_data data;
//     t_cmd cmd1, cmd2;
//     t_varenv *env_list;
//     t_redirection redir1, redir2, redir_input, redir_output;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation de l'environnement
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Configuration des heredocs (`<< EOF << EOF`)
//     redir1.type = REDIR_HEREDOC;
//     redir1.file_name = strdup("EOF");
//     redir1.next = &redir2;

//     redir2.type = REDIR_HEREDOC;
//     redir2.file_name = strdup("EOF");
//     redir2.next = &redir_input; // 🔹 Chaînage vers la redirection d’entrée

//     // 🔹 Configuration de la redirection d'entrée (`< input.txt`)
//     redir_input.type = REDIR_IN;
//     redir_input.file_name = strdup("input.txt");
//     redir_input.next = NULL; // 🔹 Fin des redirections pour `cat`

//     // 🔹 Commande 1 : `cat << EOF << EOF < input.txt`
//     cmd1.value = strdup("cat");
//     cmd1.argv = (char *[]){"cat", NULL};
//     cmd1.argc = 1;
//     cmd1.redirection = &redir1; // 🔹 Premier heredoc
//     cmd1.next = &cmd2;

//     // 🔹 Configuration de la redirection de sortie (`> output.txt`)
//     redir_output.type = REDIR_OUT;
//     redir_output.file_name = strdup("output.txt");
//     redir_output.next = NULL;

//     // 🔹 Commande 2 : `tr 'a-z' 'A-Z' > output.txt`
//     cmd2.value = strdup("tr");
//     cmd2.argv = (char *[]){"tr", "a-z", "A-Z", NULL};
//     cmd2.argc = 3;
//     cmd2.redirection = &redir_output;
//     cmd2.next = NULL;  // 🔹 Dernière commande du pipeline

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd1;
//     data.lst_exit = 0;

//     // 🔹 Exécution du test
//     printf("\n🔽🔽🔽 DÉBUT DU TEST PIPELINE AVEC HEREDOCS + REDIRECTIONS 🔽🔽🔽\n");
//     printf("▶ Exécution du pipeline : cat << EOF << EOF < input.txt | tr 'a-z' 'A-Z' > output.txt\n");
//     printf("----------------------------------------------------\n");

//     executer(&data);  // 🔹 Exécuter le pipeline

//     printf("----------------------------------------------------\n");
//     printf("🔼🔼🔼 FIN DU TEST PIPELINE 🔼🔼🔼\n");

//     // 🔹 Nettoyage mémoire
//     free(cmd1.value);
//     free(cmd2.value);
//     free(redir1.file_name);
//     free(redir2.file_name);
//     free(redir_input.file_name);
//     free(redir_output.file_name);
//     free_varenv(data.varenv_lst);

//     return 0;
// }


// int main(int argc, char **argv, char **envp)
// {
//     t_data data;
//     t_cmd cmd1, cmd2, cmd3;
//     t_varenv *env_list;
//     t_redirection redir_A, redir_B, redir_C;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation de l'environnement
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;
//     data.lst_exit = 0;

//     // 🔹 Configuration des heredocs (`<< A`, `<< B`, `<< C`)
//     ft_bzero(&redir_A, sizeof(t_redirection));
//     redir_A.type = REDIR_HEREDOC;
//     redir_A.file_name = strdup("A");
//     redir_A.next = NULL;  // Pas de chaînage ici !

//     ft_bzero(&redir_B, sizeof(t_redirection));
//     redir_B.type = REDIR_HEREDOC;
//     redir_B.file_name = strdup("B");
//     redir_B.next = NULL;  // Pas de chaînage ici !

//     ft_bzero(&redir_C, sizeof(t_redirection));
//     redir_C.type = REDIR_HEREDOC;
//     redir_C.file_name = strdup("C");
//     redir_C.next = NULL;  // Pas de chaînage ici !

//     // 🔹 Commande 1 : `cat << A`
//     ft_bzero(&cmd1, sizeof(t_cmd));
//     cmd1.value = strdup("cat");
//     cmd1.argv = (char *[]){"cat", NULL};
//     cmd1.argc = 1;
//     cmd1.redirection = &redir_A;  // `cat` utilise SEULEMENT `A`
//     cmd1.next = &cmd2;

//     // 🔹 Commande 2 : `cat << B`
//     ft_bzero(&cmd2, sizeof(t_cmd));
//     cmd2.value = strdup("cat");
//     cmd2.argv = (char *[]){"cat", NULL};
//     cmd2.argc = 1;
//     cmd2.redirection = &redir_B;  // `cat` utilise SEULEMENT `B`
//     cmd2.next = &cmd3;

//     // 🔹 Commande 3 : `cat << C`
//     ft_bzero(&cmd3, sizeof(t_cmd));
//     cmd3.value = strdup("cat");
//     cmd3.argv = (char *[]){"cat", NULL};
//     cmd3.argc = 1;
//     cmd3.redirection = &redir_C;  // `cat` utilise SEULEMENT `C`
//     cmd3.next = NULL;  // Dernière commande du pipeline

//     // 🔹 Configuration du pipeline
//     data.cmd_lst = &cmd1;

//     // 🔹 Affichage du test
//     printf("\n🔽🔽🔽 Test PIPELINE avec plusieurs HEREDOCS 🔽🔽🔽\n");
//     printf("▶ Exécution : cat << A | cat << B | cat << C\n");
//     printf("----------------------------------------------------\n");

//     // 🔹 Exécuter la commande via `executer`
//     executer(&data);

//     // 🔹 Nettoyage mémoire
//     free(cmd1.value);
//     free(cmd2.value);
//     free(cmd3.value);
//     free(redir_A.file_name);
//     free(redir_B.file_name);
//     free(redir_C.file_name);
//     free_varenv(data.varenv_lst);

//     return 0;
// }


// int main(int argc, char **argv, char **envp)
// {
//     t_data data;
//     t_cmd cmd;
//     t_varenv *env_list;
//     t_redirection redir_A, redir_B;

//     (void)argc;
//     (void)argv;

//     // 🔹 Initialisation d'un environnement minimaliste
//     env_list = init_varenv(envp);
//     data.varenv_lst = env_list;

//     // 🔹 Configuration des heredocs (`<< A << B`)
//     redir_A.type = REDIR_HEREDOC;
//     redir_A.file_name = strdup("HA");
//     redir_A.next = &redir_B;

//     redir_B.type = REDIR_HEREDOC;
//     redir_B.file_name = strdup("HB");
//     redir_B.next = NULL;

//     // 🔹 Commande : `cat << A << B`
//     cmd.value = strdup("cat");
//     cmd.argv = (char *[]) {"cat", NULL};
//     cmd.argc = 1;
//     cmd.redirection = &redir_A;
//     cmd.next = NULL;

//     // 🔹 Configuration de `t_data`
//     data.cmd_lst = &cmd;
//     data.lst_exit = 0;

//     // 🔹 Lancement du test
//     printf("\n🔽🔽🔽 DÉBUT DU TEST HEREDOC SIMPLE 🔽🔽🔽\n");
//     printf("▶ Exécution : cat << A << B\n");
//     printf("----------------------------------------------------\n");

//     executer(&data); // 🔹 Exécuter la commande

//     printf("----------------------------------------------------\n");
//     printf("🔼🔼🔼 FIN DU TEST 🔼🔼🔼\n");

//     // 🔹 Nettoyage mémoire
//     free(cmd.value);
//     free(redir_A.file_name);
//     free(redir_B.file_name);
//     free_varenv(data.varenv_lst);

//     return 0;
// }
