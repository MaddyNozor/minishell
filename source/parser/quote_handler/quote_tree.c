/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/18 17:58:18 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/init_shell.h"

char	*ft_expand_varenv(char *var_found, t_varenv *varenv)
{
	char	*expanded_value;
	char	*var_name;

	expanded_value = NULL;
	var_name = var_found + 1;
	if (ft_var_exists(var_name, varenv))
		expanded_value = ft_expand(var_name, varenv);
	else
		expanded_value = NULL;
	free(var_found);
	return (expanded_value);
}
