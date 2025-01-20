/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/01/20 17:36:41 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    t_data   data;
    
    if (ac != 1)
        return (1);
    (void)av;//on se sert pas de av, pour eviter msg d'erreur
    ft_bzero(&data, sizeof(t_data));//Initialiser memoire shell a 0 avec ft_bzero ?
    data.varenv_lst = init_varenv(envp);//Initialiser la structure du shell
    while(1)
    {
        ft_start_minishell(&data, envp);
    }
    ft_free_all(data);
    return (0);
    
}