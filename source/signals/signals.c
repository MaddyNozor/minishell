/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:28:31 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/12 19:30:47 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

extern volatile int	g_sig_captured;

static void	sigint_handler(int sig)
{
	g_sigreceiver = sig;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "\n", 1);
}

static void	sigquit_handler(int sig)
{
	g_sigreceiver = sig;
	// printf("\033[2D\033[0K");
	rl_on_new_line();
	rl_redisplay();
}

void	init_signal(void)
{
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, sigint_handler);
}