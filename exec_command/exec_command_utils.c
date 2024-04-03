/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:01:49 by udumas            #+#    #+#             */
/*   Updated: 2024/04/02 17:14:05 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		open_file_error(char *file, t_list **env_list);

int	setup_built_in(t_ast *command, char **command_str, int *exit_status,
		t_list **env_list)
{
	if (command->token->token == NULL)
		return (0);
	*command_str = build_command(command);
	*exit_status = 1871;
	*exit_status = manage_built_in(ft_split(*command_str, ' '), env_list,
			*command_str, command);
	return (1);
}

char	**setup_command_split(char **command)
{
	char	**cmd_split;

	cmd_split = ft_split(*command, ' ');
	if (cmd_split[0] == NULL)
	{
		free(cmd_split[0]);
		free(cmd_split);
		cmd_split = malloc(2 * sizeof(char *));
		cmd_split[0] = ft_strdup("''");
		cmd_split[1] = NULL;
	}
	return (cmd_split);
}

void	create_absolute_command(char **cmd_split, t_list **env_list,
		int *exit_status, char **instruct)
{
	char	**env;

	env = redo_env(*env_list);
	if (access(cmd_split[0], F_OK | X_OK) != 0)
	{
		if ((ft_strncmp(cmd_split[0], "./", 2) == 0 || ft_strncmp(cmd_split[0],
					"/", 1) == 0))
			*exit_status = open_file_error(cmd_split[0], env_list);
		else
			*instruct = check_valid_command(cmd_split, take_path(env));
	}
	else
		*instruct = ft_strdup(cmd_split[0]);
	if (*instruct == NULL && *exit_status == 1871)
	{
		ft_putstr_fd(cmd_split[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		*exit_status = 127;
		ft_end_minishell(env_list);
	}
	ft_free_char_tab(env);
}

void	dup_dup2(int *saved_fd)
{
	dup2(saved_fd[0], 0);
	dup2(saved_fd[1], 1);
}

void	ft_here_doc_error(char *limiter)
{
	ft_putstr_fd("\nminishell: warning: here-document delimited by ",
		STDOUT_FILENO);
	ft_putstr_fd("end-of-file (wanted '", STDOUT_FILENO);
	ft_putstr_fd(limiter, STDOUT_FILENO);
	ft_putstr_fd("')\n", STDOUT_FILENO);
}
