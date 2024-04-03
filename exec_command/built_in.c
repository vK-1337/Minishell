/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:01:28 by udumas            #+#    #+#             */
/*   Updated: 2024/04/03 16:56:29 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_command(char *command);
int		tablen(char **tab);
void	dup_dup2(int *saved_fd);

void	cd_management(char **command, int *exit_status, t_list **env_list)
{
	if (tablen(command) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		*exit_status = 1;
	}
	else if (command[1] == NULL)
		*exit_status = ft_cd(ft_find_var(env_list, "$HOME")->content, env_list);
	else
		*exit_status = ft_cd(command[1], env_list);
}

int	ft_in_redirections_built_in(t_ast *command, t_exec **exec, t_list **env_list)
{
	t_token	*travel;

	travel = command->token->file_redir_in;
	while (travel->next)
	{
		if (configure_fd_in3((*exec)->fd[0], travel->token,
				travel->file_redir) == -1)
			return (-1);
		if (ft_strncmp(travel->token, "<<", 2) == 0)
		{
			if (launch_here_doc(travel->file_redir, (*exec)->saved_fd,
					*env_list) == -1)
				return (-1917);
		}
		travel = travel->next;
	}
	(*exec)->fd[0] = configure_fd_in((*exec)->fd[0], travel->token,
			travel->file_redir);
	if ((*exec)->fd[0] == -1)
		return (-1);
	if (ft_strcmp(travel->token, "<<") == 0)
		(*exec)->fd[0] = launch_here_doc(travel->file_redir, (*exec)->saved_fd,
				*env_list);
	if ((*exec)->fd[0] == -1)
		return (-1917);
	return (0);
}

int	manage_built_in2(char **brut_input, t_list **env_list, t_ast *ast)
{
	char	**command;
	int		exit_status;

	command = ft_split(*brut_input, ' ');
	exit_status = check_command(command[0]);
	if (exit_status == 2)
		return (free(*brut_input), ft_exit(command,
				env_list));
	exit_status = exec_built_in(command, env_list, *brut_input, ast);
	ft_end_minishell(env_list);
	return (free(*brut_input), exit_status);
}
int	do_redirections_built_in(t_ast *command, t_list **env_list)
{
	t_exec	*exec;
	int		temp;

	init_exec(&exec);
	if (command->token->file_redir_in != NULL
		&& command->token->file_redir_out != NULL)
	{
		temp = do_redirectionsorder(command, exec->saved_fd, exec->fd,
				*env_list);
		if (temp == -1917)
			return (close_exec(&exec), ft_end_minishell(env_list), -1);
		return (close_exec(&exec), temp);
	}
	if (command->token->file_redir_in != NULL)
	{
		temp = ft_in_redirections_built_in(command, &exec, env_list);
		if (temp == -1)
			return (close_exec(&exec), -1);
		if (temp == -1917)
			return (close_exec(&exec), ft_end_minishell(env_list), -1);
	}
	if (do_redirection2(command, &exec->fd[0], &exec->fd[1]) == -1)
		return (close_exec(&exec), -1);
	return (ft_close_fd(exec->saved_fd), free(exec), 0);
}

int	manage_built_in(char **command, t_list **env_list, char *brut_input,
		t_ast *ast)
{
	int	exit_status;
	int	saved_fd[2];

	if (!command || !command[0])
		return (free(command[0]), free(command), 1871);
	exit_status = check_command(command[0]);
	saved_fd[0] = dup(0);
	saved_fd[1] = dup(1);
	if (exit_status == 0)
		return (ft_close_fd(saved_fd), ft_free_char_tab(command), 1871);
	if (do_redirections_built_in(ast, env_list) == -1)
	{
		dup_dup2(saved_fd);
		return (ft_free_char_tab(command), ft_close_fd(saved_fd), 1);
	}
	if (exit_status == 2)
	{
		dup_dup2(saved_fd);
		return (ft_close_fd(saved_fd), ft_exit(command, env_list));
	}
	exit_status = exec_built_in(command, env_list, brut_input, ast);
	dup_dup2(saved_fd);
	return (ft_close_fd(saved_fd), exit_status);
}

int	check_command(char *command)
{
	if (ft_strcmp("env", command) == 0)
		return (1);
	else if (ft_strcmp("unset", command) == 0)
		return (1);
	else if (ft_strcmp("export", command) == 0)
		return (1);
	else if (ft_strcmp("exit", command) == 0)
		return (2);
	else if (ft_strcmp("echo", command) == 0)
		return (1);
	else if (ft_strcmp("cd", command) == 0)
		return (1);
	else if (ft_strcmp("pwd", command) == 0)
		return (1);
	return (0);
}

int	exec_built_in(char **command, t_list **env_list, char *brut_input,
		t_ast *ast)
{
	int	exit_status;

	exit_status = 1871;
	if (!command)
		return (-1917);
	if (ft_strcmp("env", command[0]) == 0)
		exit_status = ft_print_env(*env_list);
	else if (ft_strcmp("unset", command[0]) == 0)
		exit_status = ft_unset(env_list, command[1]);
	else if (ft_strcmp("export", command[0]) == 0)
		exit_status = ft_export(env_list, ft_export_input(brut_input));
	else if (ft_strcmp("echo", command[0]) == 0)
		exit_status = ft_echo(command, brut_input, ast);
	else if (ft_strcmp("cd", command[0]) == 0)
		cd_management(command, &exit_status, env_list);
	else if (ft_strcmp("pwd", command[0]) == 0)
		exit_status = ft_pwd();
	return (ft_free_char_tab(command), exit_status);
}
