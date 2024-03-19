/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:27:01 by udumas            #+#    #+#             */
/*   Updated: 2024/03/19 15:28:29 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_command(char *command, char **env, t_list *env_list, t_ast *ast)
{
	char	*instruct;
	char	**cmd_split;
	int		exit_status;

	exit_status = manage_built_in(ft_split(command, ' '), env_list, command, ast);
	if (exit_status != 1871)
	{
		ft_end_minishell(&env_list);
		return (ft_free_char_tab(env), exit_status);
	}
	cmd_split = ft_split(command, ' ');
	instruct = check_valid_command(cmd_split, take_path(env));
	if (instruct == NULL && access(cmd_split[0], F_OK | X_OK) == 0)
		instruct = cmd_split[0];
	if (instruct == NULL)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);

		exit_status = 127;
		ft_end_minishell(&env_list);
	}
	else
	{
		execve(instruct, cmd_split, env);
		ft_putstr_fd(" Is a directory", 2);
		exit_status = 126;
		ft_end_minishell(&env_list);
	}
    ft_free_char_tab(cmd_split);
	return (exit_status);
}

char	*check_valid_command(char **cmd_split, char *path)
{
	char	**path_split;
	char	*temp;
	int		i;

	i = 0;
	if (path == NULL)
		return (NULL);
	path_split = ft_split(path + 5, ':');
	if (!path_split)
		return (NULL);
	while (path_split[i])
	{
		temp = add_slash(path_split[i]);
		path = ft_strjoin(temp, cmd_split[0], 0);
		if (!path)
			return (ft_free_char_tab(path_split), NULL);
		free(temp);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_char_tab(path_split), path);
		free(path);
		i++;
	}
	path = NULL;
	return (ft_free_char_tab(path_split), path);
}

int	exec_shell_command(t_ast *command, t_list *env_list, char **env, t_ast *ast)
{
	int		id;
	int		exit_status;
	char	*command_str;
	int     saved_std[2];

	saved_std[0] = dup(0);
	saved_std[1] = dup(1);
	if (command->token->token == NULL)
		return (ft_free_char_tab(env), 0);
	command_str = build_command(command);
	exit_status = 1871;
	exit_status = manage_built_in(ft_split(command_str, ' '), env_list, command_str, command);
	if (exit_status != 1871)
		return (ft_free_char_tab(env), free(command_str), exit_status);
	id = fork();
	handle_error(id, "fork");
	if (id == 0)
	{
		if (do_redirections(command, saved_std) == -1917)
		{
			ft_end_minishell(&env_list);
			return (ft_free_char_tab(env), free(command_str), 1);
		}
		exit_status = exec_command(command_str, env, env_list, ast);
	}
	else
    {
		waitpid(id, &exit_status, 0);
        exit_status = exit_status >> 8;
    }
	return (ft_free_char_tab(env), free(command_str), exit_status);
}
