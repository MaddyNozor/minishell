/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/09 18:22:12 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init_shell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	
	if (ac != 1)
		return (1);
	(void)av;
	(void)envp;
	ft_bzero(&data, sizeof(t_data));
	data.varenv_lst = init_varenv(envp);
	ft_start_minishell(&data);
	//ft_free_all(data);
	return (0);
}

// TODO RESTE A FAIRE
//- Verif leak lexing-quote (Maddy)
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