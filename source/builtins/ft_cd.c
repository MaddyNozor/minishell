/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:21:32 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/18 12:41:16 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	update_env_var(t_varenv *varenv, char *key, char *value)
{
	t_varenv	*current;

	current = varenv;
	while (current)
	{
		if (ft_strcmp(current->name, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	create_varenv(&varenv, key, value, false);
}

void	ft_update_pwd(t_varenv *varenv)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_env_var(varenv, "PWD", cwd);
		free(cwd);
	}
	else
		perror("getcwd");
}

int	ft_cd(t_cmd *cmd, t_varenv *varenv)
{
	char	*path;
	char	*home;
	int		ret;

	path = NULL;
	ret = 0;
	if (cmd->argc == 1 || !cmd->argv[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			return (89);
		}
		path = home;
	}
	else
		path = cmd->argv[1];
	if (chdir(path) == -1)
	{
		perror("cd");
		return (78);
	}
	ft_update_pwd(varenv);
	return (ret);
}


// void	ft_cd(t_cmd *cmd, t_varenv *varenv)
// {
// 	char	*path;
// 	char	*home;

// 	if (cmd->argc == 1 || !cmd->argv[1])
// 	{
// 		home = getenv("HOME");
// 		if (home)
// 		{
// 			if (chdir(home) == -1)
// 				perror("cd");
// 			else
// 				ft_update_pwd(varenv);
// 		}
// 		else
// 			fprintf(stderr, "cd: HOME not set\n");
// 	}
// 	else
// 	{
// 		path = cmd->argv[1];
// 		if (chdir(path) == -1)
// 			perror("cd");
// 		else
// 			ft_update_pwd(varenv);
// 	}
// }
