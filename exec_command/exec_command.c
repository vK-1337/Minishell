/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:27:01 by udumas            #+#    #+#             */
/*   Updated: 2024/04/01 13:06:21 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file_error(char *file, t_list **env_list)
{
	ft_end_minishell(env_list);
	if (access(file, F_OK) == -1)
	{
		perror(file);
		return (127);
	}
	else if (chdir(file) == -1)
	{
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		return (126);
	}
	else
	{
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		return (126);
	}
}

int	exec_command(char **command, char **env, t_list **env_list, t_ast *ast)
{
	char	*instruct;
	char	**cmd_split;
	int		exit_status;

	exit_status = manage_built_in(ft_split(*command, ' '), env_list, *command,
			ast);
	instruct = NULL;
	if (exit_status != 1871)
	{
		ft_end_minishell(env_list);
		return (ft_free_char_tab(env), free(*command), exit_status);
	}
	cmd_split = setup_command_split(command);
	create_absolute_command(cmd_split, env_list, &exit_status, &instruct);
	if (instruct != NULL)
	{
		free(*command);
		execve(instruct, cmd_split, env);
		exit_status = 127;
		exit_status = open_file_error(cmd_split[0], env_list);
		return (ft_end_minishell(env_list), ft_free_char_tab(env),
			ft_free_char_tab(cmd_split), exit_status);
	}
	return (ft_free_char_tab(env), free(*command), ft_free_char_tab(cmd_split),
		exit_status);
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

int	exec_shell_command(t_ast *command, t_list **env_list, char **env,
		t_ast *ast)
{
	int		id;
	int		exit_status;
	char	*command_str;

	if (setup_built_in(command, &command_str, &exit_status, env_list) == 0)
		return (ft_free_char_tab(env), 0);
	if (exit_status != 1871)
		return (ft_free_char_tab(env), free(command_str), exit_status);
	id = fork();
	handle_error(id, "fork");
	if (id == 0)
	{
		if (do_redirections(command, (int [2]){0, 1}, *env_list) == -1917)
			return (ft_end_minishell(env_list), ft_free_char_tab(env),
				free(command_str), 1);
		exit_status = exec_command(&command_str, redo_env(*env_list), env_list,
				ast);
	}
	else
	{
		waitpid(id, &exit_status, 0);
		exit_status = exit_status >> 8;
		free(command_str);
	}
	return (ft_free_char_tab(env), exit_status);
}

void	ft_close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}
