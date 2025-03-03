/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:38:32 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/03 12:40:06 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_shell.h"

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
	{
		perror("pwd");
	}
}
