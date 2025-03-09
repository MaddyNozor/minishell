/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/09 15:59:59 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

// Vire uniquement les quotes en debut et fin de token.
// Pour les token multiquotes c'est pqs qdqpté.
char	*ft_trim_quote(char const *s1, char const q)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*new_s;

	if (s1 == NULL || !q)
		return (NULL);
	start = 0;
	if (s1[start] && s1[start] == q)
		start++;
	end = ft_strlen(s1);
	if (s1[end - 1] == q)
		end--;
	new_s = malloc(((end - start) + 1) * sizeof(char));
	if (new_s == 0)
		return (0);
	i = 0;
	while (end > (start + i))
	{
		new_s[i] = s1[start + i];
		i++;
	}
	new_s[i] = '\0';
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

char	*ft_cut_quoted_text(char *content, int *i, t_varenv *lst, bool prev_hd)
{
	char	quote;
	int		start;
	char	*slice;
	char	*tmp;

	quote = content[*i];
	start = *i;
	slice = NULL;
	tmp = NULL;
	(*i)++;
	while (content[*i] && content[*i] != quote)
		(*i)++;
	slice = ft_substr(content, start + 1, *i - start);
	if (!slice)
		return (NULL);
	if (quote == '"' && prev_hd == false)
		slice = ft_varenv_manager(slice, lst);
	tmp = ft_trim_quote(slice, quote);
	free(slice);
	slice = tmp;
	(*i)++;
	return (slice);
}
