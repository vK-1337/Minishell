/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:55:09 by udumas            #+#    #+#             */
/*   Updated: 2024/03/16 17:54:37 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	check_command(char *command);

int	last_pipe(char **env, t_ast *command, t_list *env_list, t_exec **exec)
{
	int		id;
	int		exit_status;
	char	*command_str;

	command_str = build_command(command);
	id = fork();
	(*exec)->last = 1;
	(*exec)->fd[0] = -1000;
	(*exec)->fd[1] = -1000;
	handle_error(id, "fork");
	if (id == 0)
	{
		close((*exec)->fd[0]);
		char *command2 = build_command(command);
		if (check_command(command2) == 0)
		{
			if (do_pipe_redirections(command, exec) == -1917)
			{
				ft_end_minishell(&env_list);
				return (-1917);
			}
		}
		exit_status = exec_command(command_str, env, env_list, command);
		ft_putnbr_fd(exit_status, 2);
		return (exit_status);
	}
	else
	{
		waitpid(id, &exit_status, 0);
		close(0);
		while (wait(NULL) > 0)
			continue ;
		exit_status = exit_status >> 8;
	}
	return (free(command_str), exit_status);
}

int	right_pipe(t_ast *node, t_list *env_list, t_exec **exec)
{
	t_ast	*travel;
	int		exit_status;
	char	**env;

	env = redo_env(env_list);
	travel = node;
	while (is(travel->right->token->token, "|") == 1)
	{
		pipe_chain(env, node->left, env_list, exec);
		travel = travel->left;
	}
	pipe_chain(env, node->left, env_list, exec);
	exit_status = last_pipe(env, node->right, env_list, exec);
	return (exit_status);
}

int	left_pipe(t_ast *node, t_list *env_list, t_exec **exec)
{
	t_ast	*travel;
	int		exit_status;
	char	**env;

	env = redo_env(env_list);
	travel = node;
	while (is(travel->left->token->token, "|") == 1)
	{
		travel = travel->left;
	}
	pipe_chain(env, travel->left, env_list, exec);
	while (travel != node)
	{
		pipe_chain(env, travel->right, env_list, exec);
		travel = travel->daddy;
	}
	exit_status = last_pipe(env, node->right, env_list, exec);
	return (exit_status);
}

int	pipe_chain(char **env, t_ast *command, t_list *env_list, t_exec **exec)
{
	int	id;

	if (pipe((*exec)->fd) == -1)
		handle_error(-1, "pipe");
	id = fork();
	handle_error(id, "fork");
	if (id == 0)
	{
		close((*exec)->fd[0]);
		char *command2 = build_command(command);
		if (check_command(command2) == 0)
		{
			if (do_pipe_redirections(command, exec) == -1917)
			{
				ft_end_minishell(&env_list);
				return (-1917);
			}
		}
		exec_command(build_command(command), env, env_list, command);
		return (-1917);
	}
	else
	{
		close((*exec)->fd[1]);
		dup2((*exec)->fd[0], 0);
		close((*exec)->fd[0]);
	}
	return (-1917);
}
