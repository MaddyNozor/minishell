/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:02:30 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/19 16:49:29 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

static bool	validate_and_extract(char *arg, char **name, char **value, int *error_flag)
{
	*name = NULL;
	*value = NULL;
	if (!arg || ft_strlen(arg) == 0) // Cas export ""
		return (handle_invalid_identifier(arg, error_flag));
	if (!extract_name_value(arg, name, value) || !*name || ft_strlen(*name) == 0) // Cas export =
	{
		free(*name);
		free(*value);
		return (handle_invalid_identifier(arg, error_flag));
	}
	if (!*value)
		*value = ft_strdup(""); // Permet d'eviter un Segfault sur free()
	if (!is_valid_identifier(*name))
	{
		free(*name);
		free(*value);
		return (handle_invalid_identifier(arg, error_flag));
	}
	return (true);
}
static void	process_export_arg(t_data *data, char *arg, int *error_flag)
{
	char	*name;
	char	*value;

	if (!validate_and_extract(arg, &name, &value, error_flag))
		return;
	if (!ft_strchr(arg, '='))
	{
		free(name);
		free(value);
		return;
	}
	while (*value && isspace(*value))
		value++;
	if (!update_env_var(data->varenv_lst, name, value))
		create_varenv(data, &data->varenv_lst, (t_varenv_data){name, value, false});
	free(name);
	free(value);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	int	i;
	int	error_flag;

	if (cmd->argc == 1)
	{
		ft_print_list_export(data);
		return (0);
	}
	i = 1;
	error_flag = 0;
	while (i < cmd->argc)
		process_export_arg(data, cmd->argv[i++], &error_flag);
	data->lst_exit = error_flag;  // Si erreur, `$?` = 1 sinon `$?` = 0
	update_exit_status(data->varenv_lst, data->lst_exit);
	return (error_flag);
}


/*
char	*ft_substr(char const *s, unsigned int start, size_t len)
 * PARAMETERS
 * 	s: string from which to extract the new string
 * 	start: start index of the new string in the string 's'
 * 	len: maximum size of the new string


typedef struct s_cmd
{
	char					*value;
	char					**argv;
	int						argc;
	pid_t					pid;
	t_redirection			*redirection;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_varenv
{
	char					*name;
	char					*value;
	struct s_varenv			*next;
	struct s_varenv			*prev;
	bool					hiden;
}							t_varenv;
                            
typedef struct s_data
{
	t_cmd					*cmd_lst;
	t_varenv				*varenv_lst;
	t_token					*tok_lst;
	int						lst_exit;
	char					**histo;
}							t_data;
*/
        
/*
Si absence d'arguments : 
comme env tot court mais avec export devant chaque var env

Analyse argument :
- si char bloquant
    => error export
- sinon si signe = dans le token == true
    => ft_export_equal
- sinon
    => ft_export_like_this

ft_export_equal (string)
Split autour du premier egal :
    - before = NAME
    - after = value
if NAME existe deja (=comparaison avec tous les names des tokens varenv existant deja)
On prend le token var-env et on remplace la ligne value (free ancienne valeur)
free l'argument complet comme on le split
Si NAME existe deja, free name_arg
free l'ancienne value

SI name n'existe pas encore
creation nouveau token var env + ajout back list chainee
free l'arg (car on garde que le copie des parties Name et value)

ft_export_like_this
new token var env avec 
value = NULL
NAME = copie de string_arg
free argument 

ajout en fin de liste chainee
*/
