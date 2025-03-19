/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:46:35 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/19 16:12:48 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

int	ft_echo(t_cmd *cmd, t_data *data)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	if (cmd->argc > 1 && ft_strncmp(cmd->argv[1], "-n", 3) == 0)
	{
		newline = 0;
		i = 2;
	}
	while (cmd->argv[i])
	{
		write(STDOUT_FILENO, cmd->argv[i], ft_strlen(cmd->argv[i]));
		if (cmd->argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	data->lst_exit = 0; // Bash retourne toujours 0 après echo
	update_exit_status(data->varenv_lst, data->lst_exit);
	return (0);
}
