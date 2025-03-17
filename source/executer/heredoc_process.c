/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:20:07 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/17 16:04:31 by sabellil         ###   ########.fr       */
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

void	setup_heredoc_fd(t_cmd *cmd, int *heredoc_fd)
{
	t_redirection	*last_heredoc;
	t_redirection	*current;

	last_heredoc = NULL;
	current = cmd->redirection;
	while (current)
	{
		if (current->type == HEREDOC)
			last_heredoc = current;
		current = current->next;
	}
	if (last_heredoc)
	{
		// fprintf(stderr, "🛠️ Debug : Utilisation du dernier heredoc `%s`\n",
		// 	last_heredoc->file_name);
		*heredoc_fd = open(last_heredoc->file_name, O_RDONLY);
		if (*heredoc_fd == -1)
		{
			perror("Erreur ouverture heredoc");
			exit(1);
		}
	}
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

void	merge_heredoc_and_input(int heredoc_fd, int input_fd)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("ERREUR : Echec de la création du pipe");
		return ;
	}
	read_and_write(heredoc_fd, pipe_fd[1]);
	close(heredoc_fd);
	read_and_write(input_fd, pipe_fd[1]);
	close(input_fd);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
}

int	ft_create_heredoc(const char *delimiter, int index)
{
	int		fd;
	char	heredoc_filename[20];

	generate_heredoc_filename(heredoc_filename, index);
	fd = open(heredoc_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Erreur ouverture heredoc");
		return (-1);
	}
	process_heredoc_input(fd, delimiter);
	close(fd);
	fd = open(heredoc_filename, O_RDONLY);
	return (fd);
}
