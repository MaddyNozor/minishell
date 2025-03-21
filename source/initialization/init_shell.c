/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:00:05 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/21 20:13:18 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	init_existing_env(t_varenv **varenv_lst, char **envp, t_data *data)
{
	char	*equal;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			name = ft_substr(envp[i], 0, equal - envp[i]);
			value = ft_strdup(equal + 1);
			if (name && value)
				create_varenv(data, varenv_lst, (t_varenv_data){name, value, false});
			free(name);
			free(value);
		}
		i++;
	}
	if (!get_env_value(*varenv_lst, "PATH"))
		create_varenv(NULL, varenv_lst, (t_varenv_data){"PATH", "/usr/bin:/bin", false});
	create_varenv(NULL, varenv_lst, (t_varenv_data){"?", "0", false});//Est-ce qu'on a tjr besoin de cette ligne ? 
	//Genre est-ce qu'on utilise encore $? ou juste le int dans data ?
	}

void	init_minimalist_env(t_varenv **varenv_lst, t_data *data)
{
	char			*pwd;
	t_varenv_data	var_data;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	var_data = (t_varenv_data){"PWD", pwd, false};
	create_varenv(NULL, varenv_lst, var_data);
	var_data = (t_varenv_data){"SHLVL", "1", false};
	create_varenv(NULL, varenv_lst, var_data);
	var_data = (t_varenv_data){"_", "/usr/bin/env", false};
	create_varenv(NULL, varenv_lst, var_data);
	data->secret_path = ft_strdup("/usr/bin:/bin");
	free(pwd);
}

t_varenv	*init_varenv(char **envp, t_data *data)
{
	t_varenv	*varenv_lst;

	varenv_lst = NULL;
	if (!envp || !*envp)
	{
		printf("Ce minishell ne supporte pas un environnement absent \n");
		return (NULL);
		//init_minimalist_env(&varenv_lst, data);
	}
	else
		init_existing_env(&varenv_lst, envp, data);
	return (varenv_lst);
}