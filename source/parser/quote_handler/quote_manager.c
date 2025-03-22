/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 15:30:52 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/init_shell.h"

char	*ft_cut_a_slice(char *content, t_quote_ctx ctx)
{
	char	*slice;
	char	quote_type;

	slice = NULL;
	quote_type = BLANK;
	if (content[*ctx.i] == '\'' || content[*ctx.i] == '"')
		slice = ft_cut_quoted_text(content, ctx);
	else
	{
		slice = ft_cut_normal_text(content, ctx.i, quote_type);
		slice = ft_varenv_manager(slice, ctx);
	}
	if (slice == NULL)
	{
		ctx.data->lst_exit = 1;
		update_exit_status(ctx.data, 1);
	}
	return (slice);
}

void	ft_stock_the_slice(t_list **stock_list, char *slice)
{
	t_list	*new_node;

	if (!slice || !*slice)
	{
		free(slice);
		return ;
	}
	new_node = ft_lstnew(slice);
	if (!new_node)
	{
		free(slice);
		return ;
	}
	ft_lstadd_back(stock_list, new_node);
}

char	*ft_glue_the_slices_again(t_list *list_slice)
{
	char	*new_content;
	char	*temp;
	t_list	*current;

	if (!list_slice)
		return (NULL);
	new_content = ft_strdup("");
	if (!new_content)
		return (NULL);
	current = list_slice;
	while (current)
	{
		temp = ft_strjoin(new_content, current->content);
		free(new_content);
		new_content = temp;
		if (!new_content)
			return (NULL);
		current = current->next;
	}
	return (new_content);
}

char	*ft_quote_manager(t_data *data, char *actual_content, t_varenv *lst,
		bool prev_hd)
{
	t_list		*stock_list;
	char		*new_content;
	char		*slice;
	int			i;
	t_quote_ctx	ctx;

	stock_list = NULL;
	i = 0;
	ctx.i = &i;
	ctx.lst = lst;
	ctx.prev_hd = prev_hd;
	ctx.data = data;
	while (actual_content[i])
	{
		slice = ft_cut_a_slice(actual_content, ctx);
		if (slice == NULL)
			return (handle_quote_error(data, &stock_list));
		ft_stock_the_slice(&stock_list, slice);
	}
	new_content = ft_glue_the_slices_again(stock_list);
	ft_lstclear(&stock_list, free);
	free(actual_content);
	return (new_content);
}

t_token	*ft_spot_the_quotes(t_data *data)
{
	t_token	*cur_token;
	t_token	*head_of_list;
	bool	prev_is_heredoc;

	cur_token = data->tok_lst;
	head_of_list = data->tok_lst;
	prev_is_heredoc = false;
	while (cur_token != NULL)
	{
		if (cur_token->type == WORD)
		{
			if (cur_token->nb_quote > 0)
			{
				if (cur_token->prev && cur_token->prev->type == HEREDOC)
					prev_is_heredoc = true;
				cur_token->content = ft_quote_manager(data, cur_token->content,
						data->varenv_lst, prev_is_heredoc);
				if (!cur_token->content)
					return (NULL);
			}
		}
		cur_token = cur_token->next;
	}
	return (head_of_list);
}
