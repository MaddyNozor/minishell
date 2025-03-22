/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/22 15:34:34 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/init_shell.h"

static void	cpy_trim_ctn(char *dst, const char *src, size_t start, size_t end)
{
	size_t	i;

	i = 0;
	while (end > (start + i))
	{
		dst[i] = src[start + i];
		i++;
	}
	dst[i] = '\0';
}

char	*ft_trim_quote(char const *s1, char const q)
{
	size_t	start;
	size_t	end;
	char	*new_s;

	if (s1 == NULL || !q)
		return (NULL);
	start = 0;
	if (s1[start] && s1[start] == q)
		start++;
	end = ft_strlen(s1);
	if (end > 0 && s1[end - 1] == q)
		end--;
	if (end < start)
		end = start;
	new_s = malloc(((end - start) + 1) * sizeof(char));
	if (new_s == NULL)
		return (NULL);
	cpy_trim_ctn(new_s, s1, start, end);
	return (new_s);
}

char	*ft_cut_normal_text(char *content, int *i, char quote_type)
{
	int		start;
	char	*slice;

	start = *i;
	slice = NULL;
	if (quote_type == BLANK)
	{
		while (content[*i] && content[*i] != '\'' && content[*i] != '"')
			(*i)++;
	}
	else
	{
		while (content[*i] && content[*i] != quote_type)
			(*i)++;
	}
	slice = ft_substr(content, start, *i - start);
	if (slice == NULL)
		return (NULL);
	return (slice);
}

char	*ft_cut_quoted_text(char *content, t_quote_ctx ctx)
{
	char	quote;
	int		start;
	char	*slice;
	char	*tmp;

	quote = content[*ctx.i];
	start = *ctx.i;
	(*ctx.i)++;
	while (content[*ctx.i] && content[*ctx.i] != quote)
		(*ctx.i)++;
	slice = ft_substr(content, start + 1, *ctx.i - start);
	if (!slice)
		return (return_null_and_set_exit(ctx.data, 1));
	if (quote == '"' && ctx.prev_hd == false)
		slice = expand_and_check(slice, ctx);
	if (!slice)
		return (NULL);
	tmp = ft_trim_quote(slice, quote);
	free(slice);
	if (!tmp)
		return (return_null_and_set_exit(ctx.data, 1));
	slice = tmp;
	(*ctx.i)++;
	return (slice);
}

// char	*ft_cut_quoted_text(char *content, t_quote_ctx ctx)
// {
// 	char	quote;
// 	int		start;
// 	char	*slice;
// 	char	*tmp;

// 	quote = content[*ctx.i];
// 	start = *ctx.i;
// 	slice = NULL;
// 	tmp = NULL;
// 	(*ctx.i)++;
// 	while (content[*ctx.i] && content[*ctx.i] != quote)
// 		(*ctx.i)++;
// 	slice = ft_substr(content, start + 1, *ctx.i - start);
// 	if (!slice)
// 	{
// 		ctx.data->lst_exit = 1;
// 		update_exit_status(ctx.data, 1);
// 		return (NULL);
// 	}
// 	if (quote == '"' && ctx.prev_hd == false)
// 	{
// 		slice = ft_varenv_manager(slice, ctx);
// 		if (!slice)
// 		{
// 			ctx.data->lst_exit = 1;
// 			update_exit_status(ctx.data, 1);
// 			return (NULL);
// 		}
// 	}
// 	tmp = ft_trim_quote(slice, quote);
// 	free(slice);
// 	if (!tmp)
// 	{
// 		ctx.data->lst_exit = 1;
// 		update_exit_status(ctx.data, 1);
// 		return (NULL);
// 	}
// 	slice = tmp;
// 	(*ctx.i)++;
// 	return (slice);
// }
