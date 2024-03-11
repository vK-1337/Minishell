/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:27:01 by udumas            #+#    #+#             */
/*   Updated: 2024/03/11 17:35:31 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i]);
		i++;
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

char	**redo_env(t_list *env)
{
	t_list	*env_node;
	char	*env_str;
	char	*temp;
	char	**split_env;

	if (!env)
		return (NULL);
	env_node = env;
	env_str = ft_strdup("");
	if (!env_str)
		return (NULL);
	while (env_node)
	{
		temp = ft_strjoin(env_node->var_name, "=", 0);
        if (!temp)
            return (free(env_str), NULL);
		env_str = ft_strjoin(env_str, temp, 1);
		free(temp);
		env_str = ft_strjoin(env_str, env_node->content, 1);
		env_str = ft_strjoin(env_str, "\n", 1);
		if (!env_str)
			return (NULL);
		env_node = env_node->next;
	}
	split_env = ft_split(env_str, '\n');
	free(env_str);
	return (split_env);
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
void	handle_error(int err, char *msg)
{
	if (err == -1)
	{
		perror(msg);
	}
}

void	here_doc(char *limiter, int fd[2])
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(0, 1);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			close(fd[1]);
			close(fd[0]);
			get_next_line(0, 0);
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}
int	launch_here_doc(char *limiter, int saved_std[2])
{
	int fd[2];
	int	id;

	printf("limiter: %s\n", limiter);
	pipe(fd);
	dup2(saved_std[0], 0);
	id = fork();
	handle_error(id, "fork");
	if (id == 0)
	{
		here_doc(limiter, fd);
		return (-1);
	}
	else
	{
		close(fd[1]);
		wait(&id);
	}
	return (fd[0]);
}

int	configure_fd_in(int fd_in, char *token, char *file)
{
	if (fd_in != 0)
		close(fd_in);
	if (is_fd_in(token) == 1)
		fd_in = open(file, O_RDWR, 0777);
	handle_error(fd_in, file);
	return (fd_in);
}
int	configure_fd_out(int fd_out, char *token, char *file)
{
	if (fd_out != 0)
		close(fd_out);
	if (is_fd_out(token) == 1)
		fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (is_append(token) == 1)
		fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	handle_error(fd_out, file);
	return (fd_out);
}

int	do_redirections(t_ast *command)
{
	t_token	*travel;
	int		fd_out;
	int		fd_in;

	fd_out = 1;
	fd_in = 0;
	if (command->token->file_redir_in != NULL)
	{
		travel = command->token->file_redir_in;

		while (travel)
		{
			fd_in = configure_fd_in(fd_in, travel->token, travel->file_redir);
			if (ft_strncmp(travel->token, "<<", 2) == 0)
				fd_in = launch_here_doc(travel->file_redir, (int[2]){0, 1});
			if (fd_in == -1)
				return (-1917);
			travel = travel->next;
		}
	}
	if (command->token->file_redir_out != NULL)
	{
		travel = command->token->file_redir_out;
		while (travel)
		{
			configure_fd_out(fd_out, travel->token, travel->file_redir);
			travel = travel->next;
		}
	}
	if (fd_out != 1)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
	if (fd_in != 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	return (0);
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
