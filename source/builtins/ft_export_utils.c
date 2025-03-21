/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:39:51 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/21 15:05:28 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	ft_print_list_export(t_data *data)
{
	t_varenv	*current;

	current = data->varenv_lst;
	while (current)
	{
		if (current->name)
		{
			printf("export %s", current->name);
			if (current->value)
				printf("=\"%s\"", current->value);
			printf("\n");
		}
		current = current->next;
	}
	data->lst_exit = 0;
	// update_exit_status(data->varenv_lst, data->lst_exit);
	update_exit_status(data, data->lst_exit);
}

int	found_sign_equal_in_word(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

bool	extract_name_value(char *arg, char **name, char **value)
{
	int	split_pos;

	*name = NULL;
	*value = NULL;
	split_pos = found_sign_equal_in_word(arg);
	if (split_pos >= 0)
	{
		*name = ft_substr(arg, 0, split_pos);
		*value = ft_substr(arg, split_pos + 1, ft_strlen(arg) - split_pos);
	}
	else
		*name = ft_strdup(arg);
	if (!*name || (split_pos >= 0 && !*value))
	{
		free(*name);
		free(*value);
		return (false);
	}
	return (true);
}

bool	handle_invalid_identifier(char *arg, int *error_flag)
{
	printf("bash: export: `%s': not a valid identifier\n", arg);
	*error_flag = 1;
	return (false);
}

bool	is_valid_identifier(char *name)
{
	int	i;

	if (!name || !ft_isalpha(name[0]) || name[0] == '_')
		return (false);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
// int    found_sign_equal_in_word(char *str)
// {
//     int i;
    
//     i = 0;
//     while (str[i])
//     {
//         if (str[i] == '=')
//             return (i);
//         i++;
//     }
//     return (-1);   
// }

// bool    is_valid_name(char *name)
// {
//     int i;
    
//     if (!name)
//         return (false);
//     i = 1;
//     while (name [i])
//     {
//         if(!ft_isalnum(name[i]) && name[i] != '_')
//             return (false);
//         i++;
//     }
//     return (true);
// }

// t_varenv *ft_check_if_varenv_exist(t_varenv *list, char *name)
// {
//     t_varenv *current;

//     current = list;
//     while (current)
//     {
//         if (ft_strcmp(current->name, name) == 0 )
//             return current;
//         current = current->next;
//     }
//     return (NULL);
// }

// void    free_name_value_if_invalid(char **name, char **value)
// {
//     if (*name)
//     {
//         printf("export: '%s' : not a valid identifier \n", *name);
//         free(*name);
//     }
//     else if (*value)
//         free(*value);
//     return;
// }

// int    ft_replace_varenv_value(char **name, char **value, t_varenv *varenv)
// {
//     if (*value)
//     {
//         free(varenv->value);
//         varenv->value = *value;
//     }
//     free(*name);
//     return (SUCCESS);
// >>>>>>> built-in-maddy
// }
