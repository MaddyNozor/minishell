/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:00:05 by sabellil          #+#    #+#             */
/*   Updated: 2025/01/20 17:52:40 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

void    create_varenv(t_varenv **varenv_lst, char *name, char *value, bool hiden)
{
    t_varenv    *new_node;
    t_varenv    *current_node;

    new_node = malloc(sizeof(t_varenv));
    if (!new_node)
        return;
    new_node->name = ft_strdup(name);
    new_node->value = ft_strdup(value);
    new_node->hiden = hiden;// systeme bool a init qqpart?
    new_node->next = NULL;
    new_node->prev = NULL;
    if (!new_node->name || !new_node->value)//fonction free_node pour racourcir
    {
        free(new_node->name);
        free(new_node->value);
        free(new_node);
        return ;
    }
    if (!*varenv_lst)//si c'est le premier noeud, ajout a la tete de liste
        *varenv_lst = new_node;
    else//parcourir la liste pour ajouter a la fin
    {
        current_node = *varenv_lst;
        while (current_node->next)
            current_node = current_node->next;
        current_node->next = new_node;
        new_node->prev = current_node;
    }

}

void    init_existing_env(t_varenv **varenv_lst, char **envp)
{
    char    *equal;
    char    *name;
    char    *value;
    int     i;

    i = 0;
    while (envp[i])
    {
        equal = ft_strchr(envp[i], '=');
        if (equal)
        {
            name = ft_substr(envp[i], 0, equal - envp[i]);
            value = ft_strdup(equal + 1);
            if (name && value)
                create_varenv(varenv_lst, name, value, false);
            free(name);
            free(value);
        }
        i++;
    }
}

void    init_minimalist_env(t_varenv **varenv_lst)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);//Renvoie dans pwd le chemin absolu du repertoire courant. Allocation auto de memoire (NULL), taille auto (0)
    if (!pwd)
        return ;
    create_varenv(varenv_lst, "PWD", pwd, false);
    create_varenv(varenv_lst, "SHLVL", "1", false);//SHLV : valeur standard du shell parent
    create_varenv(varenv_lst, "_", "/usr/bin/env", false);//valeur neutre pour un lancement de shell RAJOUTER PATH
    free(pwd);
}

t_varenv    *init_varenv(char **envp)
{
    t_varenv    *varenv_lst;

    varenv_lst = NULL;
    if (!envp || !*envp)
        init_minimalist_env(&varenv_lst);
    else
        init_existing_env(&varenv_lst, envp);
    return(varenv_lst);
}
//a supprimer
void print_varenv(t_varenv *varenv_lst)
{
    t_varenv *current = varenv_lst;
    while (current)
    {
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
    }
}

void free_varenv(t_varenv *varenv_lst)
{
    t_varenv *current = varenv_lst;
    t_varenv *next;
    while (current)
    {
        next = current->next;
        free(current->name);
        free(current->value);
        free(current);
        current = next;
    }
}

int main(int argc, char **argv, char **envp)
{
    t_varenv *varenv_lst;

    (void)argc; // On ignore les arguments du programme
    (void)argv;

    if (envp[0] == NULL) // Cas où `env -i` est utilisé (environnement vide)
    {
        printf("Lancement avec environnement vide (env -i).\n");
        varenv_lst = init_varenv(NULL); // Appel avec NULL pour un environnement minimaliste
    }
    else
    {
        printf("Lancement avec l'environnement actuel.\n");
        varenv_lst = init_varenv(envp); // Appel avec l'environnement fourni
    }

    // Affiche les variables d'environnement
    printf("Variables d'environnement :\n");
    print_varenv(varenv_lst);

    // Libère la mémoire allouée
    free_varenv(varenv_lst);

    return (0);
}