/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mairivie <mairivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/01/20 17:29:50 by mairivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//# include "../include/minishell.h"
# include "../include/lexing.h"

t_data  *ft_init_data(t_data *data)
{
    data = malloc(sizeof(t_data));
    if (data == NULL)
        return (NULL);
    ft_bzero(data, sizeof(t_data));
    return (data);
}

int main()
{
    t_data  *data;
    int i = 1;
    char    *line = ">><<<>>>";
    char *content = NULL;
    
    data = NULL;
    data = ft_init_data(data);
    if (data == NULL)
        return (FAILURE);
    content = ft_chevron(line, i);
    printf("line =%s content =%s\n", line, content);
    free(data);
    return (SUCCESS);
}
