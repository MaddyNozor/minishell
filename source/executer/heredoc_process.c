/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:20:07 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/19 11:16:08 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	process_heredoc_input(int fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (write(fd, line, strlen(line)) == -1)
			perror("write");
		if (write(fd, "\n", 1) == -1)
			perror("write");
		free(line);
	}
}

// int	ft_create_heredoc(t_data *data, const char *delimiter, int index)//TODO : V2 avec lst_exit (jamais appele?)
// {
// 	int		fd;
// 	char	heredoc_filename[20];

// 	generate_heredoc_filename(heredoc_filename, index);
// 	fd = open(heredoc_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		exit_with_error(data, heredoc_filename, strerror(errno), 1);
// 		return (-1);
// 	}
// 	process_heredoc_input(fd, delimiter);
// 	close(fd);
// 	fd = open(heredoc_filename, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		exit_with_error(data, heredoc_filename, strerror(errno), 1);
// 		return (-1);
// 	}
// 	return (fd);
// }

// int	ft_create_heredoc(const char *delimiter, int index)//TODO : A virer a la fin (ajout de lst_exit)
// {
// 	int		fd;
// 	char	heredoc_filename[20];

// 	generate_heredoc_filename(heredoc_filename, index);
// 	fd = open(heredoc_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		perror("Erreur ouverture heredoc");
// 		return (-1);
// 	}
// 	process_heredoc_input(fd, delimiter);
// 	close(fd);
// 	fd = open(heredoc_filename, O_RDONLY);
// 	return (fd);
// }

// void	setup_heredoc_fd(t_cmd *cmd, int *heredoc_fd)//TODO : A virer a la fin (ajout de lst_exit)
// {
// 	t_redirection	*last_heredoc;
// 	t_redirection	*current;

// 	last_heredoc = NULL;
// 	current = cmd->redirection;
// 	while (current)
// 	{
// 		if (current->type == HEREDOC)
// 			last_heredoc = current;
// 		current = current->next;
// 	}
// 	if (last_heredoc)
// 	{
// 		// fprintf(stderr, "🛠️ Debug : Utilisation du dernier heredoc `%s`\n",
// 		// 	last_heredoc->file_name);
// 		*heredoc_fd = open(last_heredoc->file_name, O_RDONLY);
// 		if (*heredoc_fd == -1)
// 		{
// 			perror("Erreur ouverture heredoc");
// 			exit(1);
// 		}
// 	}
// }


// void	setup_heredoc_fd(t_data *data, t_cmd *cmd, int *heredoc_fd)//TODO : V2 avec lst_exit, A virer ala fin (Jamais appele ?)
// {
// 	t_redirection	*last_heredoc;
// 	t_redirection	*current;

// 	last_heredoc = NULL;
// 	current = cmd->redirection;
// 	while (current)
// 	{
// 		if (current->type == HEREDOC)
// 			last_heredoc = current;
// 		current = current->next;
// 	}
// 	if (last_heredoc)
// 	{
// 		*heredoc_fd = open(last_heredoc->file_name, O_RDONLY);
// 		if (*heredoc_fd == -1)
// 		{
// 			exit_with_error(data, last_heredoc->file_name, strerror(errno), 1);
// 			return;
// 		}
// 	}
// }
