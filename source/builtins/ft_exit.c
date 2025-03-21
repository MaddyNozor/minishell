/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:24:58 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 15:14:00 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_cmd *cmd, t_data *data)
{
	int	exit_code;

	if (cmd->argv[1] && !is_numeric(cmd->argv[1]))
	{
		printf("bash: exit: %s: numeric argument required\n", cmd->argv[1]);
		update_exit_status(data, 2);
		ft_free_all(data);
		exit(2);
	}
	if (cmd->argv[1] && cmd->argv[2])
	{
		printf("bash: exit: too many arguments\n");
		data->lst_exit = 1;
		return (update_exit_status(data, 1));
	}
	exit_code = 0;
	if (data && data->lst_exit >= 0 && data->lst_exit <= 255)
		exit_code = data->lst_exit;
	if (cmd->argv[1])
		exit_code = ft_atoi(cmd->argv[1]) % 256;
	if (exit_code < 0 || exit_code > 255)
		exit_code = 1;
	update_exit_status(data, data->lst_exit);
	ft_free_all(data);
	exit(exit_code);
}
