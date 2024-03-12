/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:27:01 by udumas            #+#    #+#             */
/*   Updated: 2024/03/12 17:08:57 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_error(int err, char *msg)
{
	if (err == -1)
	{
		perror(msg);
	}
}

int	check_command(char **command, t_list *env_list)
{
	int	exit_status;

	exit_status = 1871;
	if (!command)
		return (-1917);
	if (ft_strcmp("env", command[0]) == 0)
		exit_status = ft_print_env(env_list);
	else if (ft_strcmp("unset", command[0]) == 0)
		exit_status = ft_unset(&env_list, command[1]);
	else if (ft_strcmp("export", command[0]) == 0)
		exit_status = ft_export(&env_list, command[1]);
	else if (ft_strcmp("exit", command[0]) == 0)
		exit_status = -1917;
	else if (ft_strcmp("cd", command[0]) == 0)
	{
		if (command[1] == NULL)
			exit_status = ft_cd(NULL, &env_list);
		else
			exit_status = ft_cd(command[1], &env_list);
	}
	else if (ft_strcmp("pwd", command[0]) == 0)
		exit_status = ft_pwd();
	return (ft_free_char_tab(command), exit_status);
}

int	exec_command(char *command, char **env, t_list *env_list)
{
	char	*instruct;
	char	**cmd_split;
	int		exit_status;

	exit_status = check_command(ft_split(command, ' '), env_list);
	if (exit_status != 1871)
		exit(exit_status);
	cmd_split = ft_split(command, ' ');
	instruct = check_valid_command(cmd_split, take_path(env));
	if (instruct == NULL && access(cmd_split[0], F_OK | X_OK) == 0)
		instruct = cmd_split[0];
	if (instruct == NULL)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit_status = -1917;
	}
	else
	{
		execve(instruct, cmd_split, env);
		printf("execve error\n");
		exit_status = -1917;
	}
	return (ft_free_char_tab(cmd_split), exit_status);
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

int	exec_shell_command(t_ast *command, t_list *env_list, char **env)
{
	int		id;
	int		exit_status;
	char	*command_str;

	command_str = build_command(command);
	exit_status = 1871;
	exit_status = check_command(ft_split(command_str, ' '), env_list);
	if (exit_status != 1871)
		return (ft_free_char_tab(env), free(command_str), exit_status);
	id = fork();
	handle_error(id, "fork");
	if (id == 0)
	{
		if (do_redirections(command) == -1917)
			return (ft_free_char_tab(env), free(command_str), -1917);
		exit_status = exec_command(command_str, env, env_list);
	}
	else
		waitpid(id, &exit_status, 0);
	return (ft_free_char_tab(env), free(command_str), exit_status);
}
