/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:38:32 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 11:10:59 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_shell.h"

int	ft_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		data->lst_exit = 0;
	}
	else
	{
		perror("pwd");
		data->lst_exit = 1;
	}
	update_exit_status(data, data->lst_exit);
	return (data->lst_exit);
}
