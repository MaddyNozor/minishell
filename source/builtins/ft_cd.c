/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:21:32 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/19 16:07:26 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

bool	update_env_var(t_varenv *varenv, char *key, char *value)
{
	t_varenv	*current;

	current = varenv;
	while (current)
	{
		if (ft_strcmp(current->name, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (true); // Indique que la variable a été mise à jour
		}
		current = current->next;
	}
	return (false); // La variable n'existait pas
}

void	ft_update_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_env_var(data->varenv_lst, "PWD", cwd);
		free(cwd);
		data->lst_exit = 0;
	}
	else
	{
		perror("getcwd");
		data->lst_exit = 1;
	}
	update_exit_status(data->varenv_lst, data->lst_exit);
}
static int	handle_cd_error(t_data *data, char *path)
{
	fprintf(stderr, "bash: cd: %s: %s\n", path, strerror(errno));
	data->lst_exit = 1;
	update_exit_status(data->varenv_lst, data->lst_exit);
	return (1);
}

int	ft_cd(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	*home;

	path = NULL;
	if (cmd->argc == 1 || !cmd->argv[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			fprintf(stderr, "bash: cd: HOME not set\n");
			data->lst_exit = 1;
			update_exit_status(data->varenv_lst, data->lst_exit);
			return (1);
		}
		path = home;
	}
	else
		path = cmd->argv[1];
	if (chdir(path) == -1)
		return (handle_cd_error(data, path));
	ft_update_pwd(data);
	data->lst_exit = 0;
	update_exit_status(data->varenv_lst, data->lst_exit);
	return (0);
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
