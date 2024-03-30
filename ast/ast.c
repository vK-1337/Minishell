/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:55:09 by udumas            #+#    #+#             */
/*   Updated: 2024/03/30 13:52:56 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	manage_built_in2(char **brut_input, t_list **env_list, t_ast *ast);
int	check_command(char *command);

int	last_pipe(char **env, t_ast *command, t_list **env_list, t_exec **exec)
{
	int		id;
	int		exit_status;
	char	*command_str;

	command_str = build_command(command);
	id = fork();
	if (handle_error(id, "fork") == -1)
		return (ft_end_minishell(env_list), ft_free_char_tab(env),
			free(command_str), 1);
	(*exec)->last = 1;
	(*exec)->fd[0] = 0;
	(*exec)->fd[1] = (*exec)->saved_fd[1];
	if (id == 0)
	{
		if (check_command(command_str) == 0)
		{
			if (do_pipe_redirections(command, exec, *env_list) == -1917)
				return (ft_end_minishell(env_list), ft_free_char_tab(env),
					free(command_str), 1);
			return (exec_command(&command_str, env, env_list, command));
		}
		return (ft_free_char_tab(env), manage_built_in2(&command_str, env_list,
				command));
	}
	return (ft_free_char_tab(env), free(command_str), wxs(id, &exit_status));
}

int	right_pipe(t_ast *node, t_list **env_list, t_exec **exec)
{
	t_ast	*travel;
	int		exit_status;

	travel = node;
	while (is(travel->right->token->token, "|") == 1)
	{
		exit_status = pipe_chain(redo_env(*env_list), node->left, env_list,
				exec);
		if (ft_find_var(env_list, "$?")->should_end == 1)
			return (ft_close_fd((*exec)->fd), exit_status);
		travel = travel->left;
	}
	exit_status = pipe_chain(redo_env(*env_list), node->left, env_list, exec);
	if (ft_find_var(env_list, "$?")->should_end == 1)
		return (ft_close_fd((*exec)->fd), exit_status);
	exit_status = last_pipe(redo_env(*env_list), node->right, env_list, exec);
	if (ft_find_var(env_list, "$?")->should_end == 1)
		return (ft_close_fd((*exec)->fd), exit_status);
	return (ft_close_fd((*exec)->fd), exit_status);
}

int	left_pipe(t_ast *node, t_list **env_list, t_exec **exec)
{
	t_ast	*travel;
	int		exit_status;

	travel = node;
	while (travel->token->type == OPERATOR && is(travel->left->token->token,
			"|") == 1)
	{
		travel = travel->left;
	}
	exit_status = pipe_chain(redo_env(*env_list), travel->left, env_list, exec);
	if (ft_find_var(env_list, "$?")->should_end == 1)
		return (ft_close_fd((*exec)->fd), exit_status);
	while (travel != node)
	{
		exit_status = pipe_chain(redo_env(*env_list), travel->right, env_list,
				exec);
		if (ft_find_var(env_list, "$?")->should_end == 1)
			return (ft_close_fd((*exec)->fd), exit_status);
		travel = travel->daddy;
	}
	exit_status = last_pipe(redo_env(*env_list), node->right, env_list, exec);
	if (ft_find_var(env_list, "$?")->should_end == 1)
		return (ft_close_fd((*exec)->fd), exit_status);
	return (ft_close_fd((*exec)->fd), exit_status);
}

int	pipe_chain(char **env, t_ast *command, t_list **env_list, t_exec **exec)
{
	int		id;
	char	*command2;
	char	*command3;

	command2 = build_command(command);
	if (pipe((*exec)->fd) == -1)
		handle_error(-1, "pipe");
	id = fork();
	handle_error(id, "fork");
	if (id == 0)
	{
		close((*exec)->fd[0]);
		if (do_pipe_redirections(command, exec, *env_list) == -1917)
			return (ft_end_minishell(env_list), free(command2),
				ft_free_char_tab(env), 1);
		if (check_command(command2) == 0)
			return (exec_command(&command2, env, env_list, command));
		command3 = build_command(command);
		return (ft_free_char_tab(env), free(command2),
			manage_built_in2(&command3, env_list, command));
	}
	return (free(command2), ft_free_char_tab(env), exit_pc(command, exec, id)
		- 1);
}
