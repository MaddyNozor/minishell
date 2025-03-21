/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:02:30 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/21 15:06:21 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

static bool	validate_and_extract(char *arg, char **name, char **value,
		int *error_flag)
{
	*name = NULL;
	*value = NULL;
	if (!arg || ft_strlen(arg) == 0) // Cas export ""
		return (handle_invalid_identifier(arg, error_flag));
	if (!extract_name_value(arg, name, value) || !*name
		|| ft_strlen(*name) == 0) // Cas export =
	{
		free(*name);
		free(*value);
		return (handle_invalid_identifier(arg, error_flag));
	}
	if (!*value)
		*value = ft_strdup(""); // Permet d'eviter un Segfault sur free()
	if (!is_valid_identifier(*name))
	{
		free(*name);
		free(*value);
		return (handle_invalid_identifier(arg, error_flag));
	}
	return (true);
}

static void	process_export_arg(t_data *data, char *arg, int *error_flag)
{
	char	*name;
	char	*value;

	if (!validate_and_extract(arg, &name, &value, error_flag))
		return ;
	if (!ft_strchr(arg, '='))
	{
		free(name);
		free(value);
		return ;
	}
	while (*value && isspace(*value))
		value++;
	if (!update_env_var(data->varenv_lst, name, value))
	{
		create_varenv(data, &data->varenv_lst,
			(t_varenv_data){name, value, false});
	}
	free(name);
	free(value);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	int	i;
	int	error_flag;

	if (cmd->argc == 1)
	{
		ft_print_list_export(data);
		return (0);
	}
	i = 1;
	error_flag = 0;
	while (i < cmd->argc)
		process_export_arg(data, cmd->argv[i++], &error_flag);
	data->lst_exit = error_flag; // Si erreur, `$?` = 1 sinon `$?` = 0
	// update_exit_status(data->varenv_lst, data->lst_exit);
	update_exit_status(data, data->lst_exit);
	return (error_flag);
}
// =======
// int ft_split_name_and_value(char **name, char **value, char *str_to_split)
// {
//     int         split_pos;
    
//     split_pos = found_sign_equal_in_word(str_to_split);
//     if (split_pos >= 0)
//     {
//         *name = ft_substr(str_to_split, 0, split_pos);
//         if(*name == NULL)
//             return (FAILURE); //code erreur malloc
//         *value = ft_substr(str_to_split, split_pos + 1, 
//             ft_strlen(str_to_split) - split_pos);
//         if(*value == NULL)
//             return (FAILURE); //code erreur malloc
//             //FAUX, y avait peut etre juste pas de value !!!
//     }
//     else
//     {   
//         *name = ft_strdup(str_to_split);
//         if(*name == NULL)
//             return (FAILURE); //code erreur malloc
//     }
//     return (SUCCESS);
// }

// void    ft_create_exported_varenv(char **name, char **value, t_varenv *list)
// {
//     t_varenv    *already_exist;

//     already_exist = NULL;
//     if (*value == NULL)
//     {
//         free(*name);
//         return;   
//     }
//     if (*name)
//         already_exist = ft_check_if_varenv_exist(list, *name);
//     if (already_exist != NULL)
//         ft_replace_varenv_value(name, value, already_exist);
//     else if (*name != NULL && *value != NULL)
//         create_varenv(&list, *name, *value, false);
// }

// int       ft_export(t_data *data, t_cmd *cmd)
// {
//     int         i;
//     char        *name;
//     char        *value;

//     if (cmd->argc == 1)
//         return (ft_print_list_export(data), SUCCESS);
//     i = 1;
//     while (i < cmd->argc)
//     {
//         name = NULL;
//         value = NULL; 
//         if (ft_split_name_and_value(&name, &value, cmd->argv[i]) == false)
//             return (FAILURE); // code erreur malloc a fail
//         if (is_valid_name(name) == false)
//             return (free_name_value_if_invalid (&name, &value), FAILURE); //failure = code erreur not a valid ID
//         ft_create_exported_varenv(&name, &value, data->varenv_lst);
//         i++;
//     }
//     return(SUCCESS);
// }

// >>>>>>> built-in-maddy
