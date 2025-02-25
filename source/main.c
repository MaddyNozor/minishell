/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/02/24 16:53:38 by mairivie         ###   ########.fr       */
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
	// ft_bzero(&data, sizeof(t_data));
	// data.varenv_lst = init_varenv(envp);
	ft_start_minishell(&data);
	// ft_free_all(data);
	return (0);
}
