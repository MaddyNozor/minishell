/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/09 16:05:35 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

char	*ft_varenv_manager(char *string, t_varenv *lst)
{
	t_list	*stock_list;
	char	*new_content;
	char	*slice;
	int		i;

	stock_list = NULL;
	i = 0;
	while (string[i])
	{
		slice = ft_varenv_slicing(string, &i, lst);
		ft_stock_the_slice(&stock_list, slice);
	}
	new_content = ft_glue_the_slices_again(stock_list);
	ft_lstclear(&stock_list, free);
	free(string);
	return (new_content);
}

char	*ft_varenv_slicing(char *content, int *i, t_varenv *lst)
{
	char	*slice;

	slice = NULL;
	if (content[*i] == '$')
	{
		slice = ft_cut_varenv(content, i);
		slice = ft_expand_varenv(slice, lst);
	}
	else
		slice = ft_cut_normal_text_but_varenv(content, i);
	if (slice == NULL)
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
