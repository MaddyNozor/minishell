/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:30:39 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/22 11:29:31 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	ft_free_all(t_data *data)
{
	rl_clear_history();
	if (!data)
		return ;
	if (data->varenv_lst)
		free_varenv(data->varenv_lst);
	if (data->cmd_lst)
		free_cmd_list(data->cmd_lst);
	if (data->tok_lst)
		free_token_list(&data->tok_lst);
}
