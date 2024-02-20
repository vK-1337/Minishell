/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:27:01 by udumas            #+#    #+#             */
/*   Updated: 2024/02/19 21:32:57 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_path(t_list *env)
{
	t_list	*env_node;

	env_node = env;
	while (env_node)
	{
		if (ft_strncmp(env_node->var_name, "PATH", 4) == 0)
			return (env_node->content);
		env_node = env_node->next;
	}
	return (NULL);
}

void	ft_free_char_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*add_slash(char *cmd1)
{
	int		i;
	char	*cmd_slash;

	i = 0;
	while (cmd1[i])
		i++;
	cmd_slash = malloc(sizeof(char) * i + 2);
	i = 0;
	while (cmd1[i])
	{
		cmd_slash[i] = cmd1[i];
		i++;
	}
	cmd_slash[i] = '/';
	cmd_slash[i + 1] = '\0';
	return (cmd_slash);
}

char	*check_valid_command(char *cmd, char *path)
{
	char	**path_split;
	char	**cmd_split;
	char	*temp;
	int		i;

	i = 0;
	if (path == NULL)
		return (NULL);
	cmd_split = ft_split(cmd, ' ');
	path_split = ft_split(path + 5, ':');
	while (path_split[i])
	{
		temp = add_slash(path_split[i]);
		path = ft_strjoin(temp, cmd_split[0], 0);
		free(temp);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_char_tab(path_split), ft_free_char_tab(cmd_split),
				path);
		free(path);
		i++;
	}
	path = NULL;
	return (ft_free_char_tab(path_split), ft_free_char_tab(cmd_split), path);
}

char	**redo_env(t_list *env)
{
	t_list	*env_node;
	char	*env_str;
	char	*temp;
	char	**split_env;

	env_node = env;
	while (env_node)
	{
		temp = ft_strjoin(env_node->var_name, "=", 0);
		env_str = ft_strjoin("", temp, 0);
		free(temp);
		temp = ft_strjoin(env_str, env_node->content, 0);
		free(env_str);
		env_str = temp;
		temp = ft_strjoin(env_str, "\n", 0);
		free(env_str);
		env_str = temp;
		env_node = env_node->next;
	}
	split_env = ft_split(env_str, '\n');
	free(env_str);
	return (split_env);
}

int	exec_command(char *command, t_list *env)
{
	char	*instruct;

	instruct = check_valid_command(command, take_path(env));
	if (instruct == NULL)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	else
	{
		execve(instruct, ft_split(command, ' '), redo_env(env));
		printf("execve error\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	exec_shell_command(char *command, t_list *env)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		exec_command(command, env);
		exit(EXIT_SUCCESS);
	}
	else
        waitpid(id, NULL, 0);
	return (1);
}
