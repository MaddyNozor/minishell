/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:24:58 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/21 11:21:00 by sabellil         ###   ########.fr       */
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
		// update_exit_status(data->varenv_lst, 2);
		update_exit_status(data, 2);
		exit(2);
	}
	if (cmd->argv[1] && cmd->argv[2])
	{
		printf("bash: exit: too many arguments\n");
		data->lst_exit = 1;
		// update_exit_status(data->varenv_lst, 1);
		update_exit_status(data, 1);
		return ;
	}
	exit_code = 0;
	if (data && data->lst_exit >= 0 && data->lst_exit <= 255)
		exit_code = data->lst_exit;
	if (cmd->argv[1])
		exit_code = ft_atoi(cmd->argv[1]) % 256;
	if (exit_code < 0 || exit_code > 255)
		exit_code = 1;
	// update_exit_status(data->varenv_lst, exit_code);
	update_exit_status(data, data->lst_exit);
	ft_free_all(data);
	exit(exit_code);
}


// void	ft_exit(t_cmd *cmd, t_data *data)
// {
// 	int	exit_code;

// 	if (cmd->argv[1] && !is_numeric(cmd->argv[1]))
// 	{
// 		printf("bash: exit: %s: numeric argument required\n", cmd->argv[1]);
// 		update_exit_status(data->varenv_lst, 2);
// 		exit(2);
// 	}
// 	if (cmd->argv[1] && cmd->argv[2])
// 	{
// 		printf("bash: exit: too many arguments\n");
// 		data->lst_exit = 1;
// 		update_exit_status(data->varenv_lst, 1);
// 		return ;
// 	}
// 	exit_code = data->lst_exit;
// 	if (cmd->argv[1])
// 		exit_code = ft_atoi(cmd->argv[1]) % 256;
// 	update_exit_status(data->varenv_lst, exit_code);
// 	// free_cmd_list(data->cmd_lst);
// 	// free_varenv(data->varenv_lst);
// 	ft_free_all(data);
// 	exit(exit_code);
// }
