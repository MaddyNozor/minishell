/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:28:31 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/20 18:34:36 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

extern volatile sig_atomic_t	g_sig_caught;

static void	sig_int_handler(void)
{
	g_sig_caught = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_quit_handler(void)
{
	g_sig_caught = SIGQUIT;
	ft_printf("^\\Quit (core dumped)\n");
	ft_printf("\n\nIs it a bird ? Is it a plane ? No ! It's Super-SIGQUIT!\n");
	rl_redisplay();
}

// Ignore SIGQUIT (c+\) while execution
// manage SIGINT (c+c)
void	ft_init_signal_handlers(void)
{
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
}
