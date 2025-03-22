/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:39:51 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 11:10:34 by sabellil         ###   ########.fr       */
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
