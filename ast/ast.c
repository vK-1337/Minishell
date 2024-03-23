/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:55:09 by udumas            #+#    #+#             */
/*   Updated: 2024/03/23 11:58:49 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int manage_built_in2(char *brut_input, t_list **env_list, t_ast *ast);
int	check_command(char *command);

int	last_pipe(char **env, t_ast *command, t_list **env_list, t_exec **exec)
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
		if (check_command(command_str) == 0)
		{
			if (do_pipe_redirections(command, exec) == -1917)
			{
				ft_end_minishell(env_list);
				return (free(command_str), 1);
			}
			return(exec_command(&command_str, env, env_list, command));
		}
		return (manage_built_in2(command_str, env_list, command));
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

int	right_pipe(t_ast *node, t_list **env_list, t_exec **exec)
{
	t_ast	*travel;
	int		exit_status;
	char	**env;

	env = redo_env(*env_list);
	travel = node;
	while (is(travel->right->token->token, "|") == 1)
	{
		exit_status = pipe_chain(env, node->left, env_list, exec);
		if (ft_find_var(env_list, "$?")->should_end == 1)
			return (exit_status);
		travel = travel->left;
	}
	exit_status = pipe_chain(env, node->left, env_list, exec);
	if (ft_find_var(env_list, "$?")->should_end == 1)
			return (exit_status);
	exit_status = last_pipe(env, node->right, env_list, exec);
	if (ft_find_var(env_list, "$?")->should_end == 1)
			return (exit_status);
	return (exit_status);
}

int	left_pipe(t_ast *node, t_list **env_list, t_exec **exec)
{
	t_ast	*travel;
	int		exit_status;
	char	**env;

	env = redo_env(*env_list);
	travel = node;
	while (travel->token->type == OPERATOR && is(travel->left->token->token, "|") == 1)
	{
		travel = travel->left;
	}
	exit_status = pipe_chain(env, travel->left, env_list, exec);
	if (ft_find_var(env_list, "$?")->should_end == 1)
		return (exit_status);
	while (travel != node)
	{
		exit_status = pipe_chain(env, travel->right, env_list, exec);
		if (ft_find_var(env_list, "$?")->should_end == 1)
			return (exit_status);
		travel = travel->daddy;
	}
	exit_status = last_pipe(env, node->right, env_list, exec);
	if (ft_find_var(env_list, "$?")->should_end == 1)
			return (exit_status);
	return (exit_status);
}

int	pipe_chain(char **env, t_ast *command, t_list **env_list, t_exec **exec)
{
	int	id;
	char *command2;
	
	command2 = build_command(command);
	if (pipe((*exec)->fd) == -1)
		handle_error(-1, "pipe");
	id = fork();
	handle_error(id, "fork");
	if (id == 0)
	{
		close((*exec)->fd[0]);
		if (do_pipe_redirections(command, exec) == -1917)
		{
			ft_end_minishell(env_list);
			return (1);
		}
		if (check_command(command2) == 0)
		{
			exec_command(&command2, env, env_list, command);
			return (1);
		}
		return (manage_built_in2(build_command(command), env_list, command));
	}
	else
	{
		close((*exec)->fd[1]);
		dup2((*exec)->fd[0], 0);
		close((*exec)->fd[0]);
	}
	return (ft_free_char_tab(env), free(command2), -1);
}
