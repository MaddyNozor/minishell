/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 15:07:09 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/init_shell.h"

char	*ft_varenv_manager(char *string, t_quote_ctx ctx)
{
	t_list	*stock_list;
	char	*new_content;
	char	*slice;
	int		i;

	stock_list = NULL;
	i = 0;
	ctx.i = &i;
	while (string[i])
	{
		slice = ft_varenv_slicing(string, ctx);
		if (!slice)
		{
			ctx.data->lst_exit = 1;
			update_exit_status(ctx.data, 1);
			ft_lstclear(&stock_list, free);
			free(string);
			return (NULL);
		}
		ft_stock_the_slice(&stock_list, slice);
	}
	new_content = ft_glue_the_slices_again(stock_list);
	ft_lstclear(&stock_list, free);
	free(string);
	return (new_content);
}

char	*ft_varenv_slicing(char *content, t_quote_ctx ctx)
{
	char	*slice;

	slice = NULL;
	if (content[*ctx.i] == '$')
	{
		slice = ft_cut_varenv(content, ctx.i);
		if (!slice)
			return (NULL);
		slice = ft_expand_varenv(slice, ctx);
	}
	else
		slice = ft_cut_normal_text_but_varenv(content, ctx.i);
	if (!slice)
		return (NULL);
	return (slice);
}

char	*ft_cut_varenv(char *content, int *i)
{
	int		start;
	char	*slice;

	start = *i;
	slice = NULL;
	(*i)++;
	while (content[*i])
	{
		if (content[*i] == '?' || (content[*i] >= '0' && content[*i] <= '9'))
		{
			(*i)++;
			break ;
		}
		else if (content[*i] != '_' && ft_isalpha(content[*i]) == false)
			break ;
		else
			while (ft_isalnum(content[*i]) || content[*i] == '_')
				(*i)++;
	}
	slice = ft_substr(content, start, *i - start);
	if (!slice)
		return (NULL);
	return (slice);
}

char	*ft_cut_normal_text_but_varenv(char *content, int *i)
{
	int		start;
	char	*slice;

	start = *i;
	slice = NULL;
	while (content[*i] && content[*i] != '$')
		(*i)++;
	slice = ft_substr(content, start, *i - start);
	if (slice == NULL)
		return (NULL);
	return (slice);
}
