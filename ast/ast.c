/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:55:09 by udumas            #+#    #+#             */
/*   Updated: 2024/03/12 12:46:15 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	last_pipe(char **env, t_ast *command, t_list *env_list, int saved_std[2])
{
	int		id;
	int		exit_status;
	char	*command_str;

	command_str = build_command(command);
	id = fork();
	handle_error(id, "fork");
	if (id == 0)
	{
		if (do_pipe_redirections(command, (int [2]){0, 1}, saved_std) == -1917)
			return (free(command_str), -1917);
		exec_command(command_str, env, env_list);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(id, &exit_status, 0);
		while (wait(NULL) > 0)
			continue ;
	}
	return (free(command_str), exit_status);
}

int	right_pipe(t_ast *node, t_list *env_list, int saved_std[2])
{
	t_ast	*travel;
	int		exit_status;

	travel = node;
	while (is(travel->right->token->token, "|") == 1)
	{
		pipe_chain(redo_env(env_list), node->left, env_list, saved_std);
		travel = travel->left;
	}
	pipe_chain(redo_env(env_list), node->left, env_list, saved_std);
	exit_status = last_pipe(redo_env(env_list), node->right, env_list,
			saved_std);
	return (exit_status);
}

int	left_pipe(t_ast *node, t_list *env_list, int saved_std[2])
{
	t_ast	*travel;
	int		exit_status;

	travel = node;
	while (is(travel->left->token->token, "|") == 1)
	{
		travel = travel->left;
	}
	pipe_chain(redo_env(env_list), travel->left, env_list, saved_std);
	while (travel != node)
	{
		pipe_chain(redo_env(env_list), travel->right, env_list, saved_std);
		travel = travel->daddy;
	}
	exit_status = last_pipe(redo_env(env_list), node->right, env_list,
			saved_std);
	return (exit_status);
}

int	pipe_chain(char **env, t_ast *command, t_list *env_list, int saved_std[2])
{
	int	fd[2];
	int	id;

	if (pipe(fd) == -1)
		handle_error(-1, "pipe");
	id = fork();
	handle_error(id, "fork");
	if (id == 0)
	{
		if (do_pipe_redirections(command, fd, saved_std) == -1917)
			return (-1917);
		exec_command(build_command(command), env, env_list);
		return (-1917);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
	}
	return (-1917);
}
