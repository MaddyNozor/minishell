/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:28:31 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 11:35:32 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

extern volatile sig_atomic_t	g_sig_caught;

// manage SIGINT (ctrl +c)
void	sig_int_handler(sig_atomic_t g_sig_caught)
{
	g_sig_caught = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// manage SIGINT in fork (ctrl +c)
void	sig_int_handler_fork(sig_atomic_t g_sig_caught)
{
	g_sig_caught = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

// Ignore SIGQUIT (c+\) while execution
// manage SIGINT (c+c)
void	ft_init_signal_handlers(void)
{
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
static void	sig_int_handler(int signo)
{
    (void)signo; // On ignore le paramètre s'il n'est pas utilisé
    g_sig_caught = SIGINT;
    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}
*/