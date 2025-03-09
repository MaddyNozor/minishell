/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/09 17:52:53 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/init_shell.h"

char	*ft_cut_a_slice(char *content, int *i, t_varenv *lst, bool prev_hd)
{
	char	*slice;
	char	quote_type;

	slice = NULL;
	quote_type = BLANK;
	if (content[*i] == '\'' || content[*i] == '"')
	{
		quote_type = content[*i];
		slice = ft_cut_quoted_text(content, i, lst, prev_hd);
	}
	else
		slice = ft_cut_normal_text(content, i, quote_type);
	if (slice == NULL)
		return (NULL);
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
		return (ft_strdup(""));
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

char	*ft_quote_manager(char *actual_content, t_varenv *lst, bool prev_hd)
{
	t_list	*stock_list;
	char	*new_content;
	char	*slice;
	int		i;

	stock_list = NULL;
	i = 0;
	while (actual_content[i])
	{
		slice = ft_cut_a_slice(actual_content, &i, lst, prev_hd);
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
				// ft_printf("before: %s \n", cur_token->content); //TODO pour test a virer a terme
				cur_token->content = ft_quote_manager(cur_token->content,
						data->varenv_lst, prev_is_heredoc);
				// ft_printf("after: %s \n", cur_token->content);
			}
		}
		cur_token = cur_token->next;
	}
	return (head_of_list);
}
