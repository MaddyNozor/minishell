/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 15:34:45 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/init_shell.h"

char	*ft_expand_varenv(char *var_found, t_quote_ctx ctx)
{
	char	*expanded_value;
	char	*var_name;

	expanded_value = NULL;
	var_name = var_found + 1;
	if (ft_var_exists(var_name, ctx.lst))
	{
		expanded_value = ft_expand(var_name, ctx.lst);
		if (!expanded_value)
		{
			ctx.data->lst_exit = 1;
			update_exit_status(ctx.data, 1);
		}
	}
	else
		expanded_value = NULL;
	free(var_found);
	return (expanded_value);
}

char	*handle_quote_error(t_data *data, t_list **stock_list)
{
	data->lst_exit = 1;
	update_exit_status(data, 1);
	ft_lstclear(stock_list, free);
	return (NULL);
}

char	*return_null_and_set_exit(t_data *data, int code)
{
	data->lst_exit = code;
	update_exit_status(data, code);
	return (NULL);
}

char	*expand_and_check(char *slice, t_quote_ctx ctx)
{
	slice = ft_varenv_manager(slice, ctx);
	if (!slice)
		return (return_null_and_set_exit(ctx.data, 1));
	return (slice);
}
