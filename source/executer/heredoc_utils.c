/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:54:50 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/14 15:28:28 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	generate_heredoc_filename(char *filename, int index)
{
	char	num[12];
	int		i;

	i = 0;
	while (index > 0)
	{
		num[i++] = '0' + (index % 10);
		index /= 10;
	}
	num[i] = '\0';
	ft_strlcpy(filename, "heredoctemp", 20);
	ft_strlcat(filename, num, 20);
}

void	open_heredoc_file(t_redirection *redir, char *heredoc_filename)
{
	free(redir->file_name);
	redir->file_name = strdup(heredoc_filename);
	if (!redir->file_name)
	{
		perror("Erreur malloc");
		exit(1);
	}
}

// void	create_heredoc_file(t_redirection *redir, int index)
// {
// 	char	heredoc_filename[20];
// 	int		fd;
// 	char	*delimiter;

// 	generate_heredoc_filename(heredoc_filename, index);
// 	delimiter = strdup(redir->file_name);
// 	if (!delimiter)
// 	{
// 		perror("Erreur malloc");
// 		exit(1);
// 	}
// 	open_heredoc_file(redir, heredoc_filename);
// 	fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		perror("Erreur ouverture heredoc");
// 		exit(1);
// 	}
// 	// fprintf(stderr,
// 	// 	"🛠️ Debug : Remplissage du heredoc `%s` (Délimiteur attendu : `%s`)\n",
// 	// 	redir->file_name, delimiter);
// 	process_heredoc_input(fd, delimiter);
// 	close(fd);
// 	free(delimiter);
// }
void	create_heredoc_file(t_redirection *redir, int index)
{
    char    heredoc_filename[20];
    int     fd;
    char    *delimiter;

    generate_heredoc_filename(heredoc_filename, index);
    delimiter = strdup(redir->file_name);
    if (!delimiter)
    {
        perror("Erreur malloc");
        exit(1);
    }
    open_heredoc_file(redir, heredoc_filename);
    fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Erreur ouverture heredoc");
        exit(1);
    }
    process_heredoc_input(fd, delimiter);
    close(fd);
    free(delimiter);
}


void	unlink_heredoc_temp(t_redirection *redirection)
{
	t_redirection	*current;

	current = redirection;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (unlink(current->file_name) == -1)
			{
				perror("unlink");
			}
			// else
			// {
			// 	printf("✅ Heredoc %s supprimé\n", current->file_name);
			// }
		}
		current = current->next;
	}
}

bool	contains_heredoc(t_redirection *redirection)
{
	t_redirection	*current;

	current = redirection;
	while (current)
	{
		if (current->type == HEREDOC)
			return (true);
		current = current->next;
	}
	return (false);
}
