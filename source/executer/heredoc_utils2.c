/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:03:13 by sabellil          #+#    #+#             */
/*   Updated: 2025/03/09 16:29:28 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

void	create_heredoc_list(t_cmd *cmd_lst, char *last_heredoc_files[])
{
	t_cmd			*current_cmd;
	t_redirection	*redir;
	int				cmd_index;

	current_cmd = cmd_lst;
	cmd_index = 0;
	while (current_cmd)
	{
		redir = current_cmd->redirection;
		last_heredoc_files[cmd_index] = NULL;
		while (redir)
		{
			if (redir->type == HEREDOC)
				last_heredoc_files[cmd_index] = redir->file_name;
			redir = redir->next;
		}
		cmd_index++;
		current_cmd = current_cmd->next;
	}
}

void	handle_heredoc_input(char *heredoc_file)
{
	int	fd;

	if (heredoc_file)
	{
		fd = open(heredoc_file, O_RDONLY);
		if (fd == -1)
		{
			perror("Erreur ouverture heredoc");
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}
