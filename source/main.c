/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 11:16:27 by mairivie         ###   ########.fr       */
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
	data.lst_exit = 0;
	data.varenv_lst = init_varenv(envp, &data);
	if (data.varenv_lst == NULL)
		return (0);
	ft_init_signal_handlers();
	ft_start_minishell(&data);
	return (0);
}
