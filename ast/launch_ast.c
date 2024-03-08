/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:56:17 by udumas            #+#    #+#             */
/*   Updated: 2024/03/08 19:28:08 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	launch_ast(char *input, t_list *env_list, int *exit_status)
{
	//int		exit_status;
	t_ast	*ast;

	ast = NULL;
	if (!env_list)
		return (-1917);
	if (create_ast_list(&ast, ft_lexer(input, &env_list)) == NULL)
		return (-1917);
	if (!ast)
	{
		printf("Memory error\n");
		return (-1);
	}
	//read_ast(ast, 0);	
	launch_ast_recursive(ast, env_list, exit_status);
	ft_free_ast(ast);
	return (*exit_status);
}
void	export_and_wildcard(t_ast *ast, t_list *env_list)
{
	t_token	*travel;
	
	if (ast == NULL)
		return ;
	travel = ast->token;
	while (travel)
	{
		travel->token = ft_expand(travel->token, &env_list);
		travel = travel->next;
	}
	if (ast->token->file_redir_in)
	{
		travel = ast->token->file_redir_in;
		while (travel)
		{
			travel->file_redir = ft_expand(travel->file_redir, &env_list);
			travel = travel->next;
		}
	}
	if (ast->token->file_redir_out)
	{
		travel = ast->token->file_redir_out;
		while (travel)
		{
			travel->file_redir = ft_expand(travel->file_redir, &env_list);
			travel = travel->next;
		}
	}
	export_and_wildcard(ast->left, env_list);
	export_and_wildcard(ast->right, env_list);
}

int	launch_ast_recursive(t_ast *ast, t_list *env_list, int *exit_status)
{
	char	**env;

	env = NULL;
	
	export_and_wildcard(ast, env_list);
	if (ast == NULL)
		return (0);
	else if (ast->token->type == PARENTHESIS)
		parenthesis(ast, env_list, exit_status);
	else if (is_and(ast->token->token) == 1 && launch_ast_recursive(ast->left, env_list, exit_status) == 0)
		launch_ast_recursive(ast->right, env_list, exit_status);
	else if (is_or(ast->token->token) == 1 && launch_ast_recursive(ast->left,
			env_list, exit_status) != 0)
		launch_ast_recursive(ast->right, env_list, exit_status);
	else if (ast->token->type == 3 && is_pipe(ast->token->token) == 1)
		*exit_status = create_redirection(ast, env_list);
	else if (ast->token->type == 0)
	{
		env = redo_env(env_list);
		*exit_status = exec_shell_command(ast, env_list, env);
	}
	return (*exit_status);
}

char	*build_command(t_ast *node)
{
	t_token	*travel;
	char	*command;

	travel = node->token;
	command = ft_strdup(node->token->token);
	if (!command)
		return (NULL);
	travel = travel->next;
	while (travel != NULL)
	{
		command = ft_strjoin(command, " ", 1);
		command = ft_strjoin(command, travel->token, 1);
		if (!command)
			return (NULL);
		travel = travel->next;
	}
	return (command);
}
void	do_pipe_redirections(t_ast *command, int fd[2], int saved_std[2])
{
	t_token	*travel;

	travel = command->token->file_redir_in;
	while (travel)
	{
		fd[0] = configure_fd_in(fd[0], travel->token, travel->file_redir, saved_std);
		travel = travel->next;
	}
	travel = command->token->file_redir_out;
	while (travel)
	{
		fd[1] = configure_fd_out(fd[1], travel->token, travel->file_redir);
		travel = travel->next;
	}
	dup2(fd[0], 0);
	dup2(fd[1], 1);
}

int	last_pipe(char **env, t_ast *command, int fd_out, t_list *env_list, int saved_std[2])
{
	int		id;
	int		exit_status;
	char	*command_str;

	command_str = build_command(command);
	id = fork();
	handle_error(id, "fork");
	if (id == 0)
	{
		do_pipe_redirections(command, (int[2]){0, 1}, saved_std);
		exec_command(command_str, env, env_list);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(id, &exit_status, 0);
		if (fd_out != 1)
			close(fd_out);
	}
	free(command_str);
	return (exit_status);
}

int	create_redirection(t_ast *node, t_list *env_list)
{
	int	exit_status;
    int saved_std[2];
	
	saved_std[0] = dup(0);
	saved_std[1] = dup(1);
	if (is_pipe(node->left->token->token) == 1)
        exit_status = left_pipe(node, env_list, saved_std);
    else if (is_pipe(node->right->token->token) == 1)
        exit_status = right_pipe(node, env_list, saved_std);
    else
    {
        exit_status = pipe_chain(redo_env(env_list), node->left, env_list, saved_std);
        exit_status = last_pipe(redo_env(env_list), node->right, 1, env_list, saved_std);
    }
	dup2(saved_std[0], 0);
	close(saved_std[0]);
	close(saved_std[1]);
	return (exit_status);
}


int right_pipe(t_ast *node, t_list *env_list, int saved_std[2])
{
    t_ast   *travel;
    int     exit_status;
    travel = node;
    
    while (is_pipe(travel->right->token->token) == 1)
    {
        exit_status = pipe_chain(redo_env(env_list), node->left, env_list, saved_std);
        travel = travel->left;
    }
    exit_status = pipe_chain(redo_env(env_list), node->left, env_list, saved_std);
	last_pipe(redo_env(env_list), node->right, 1, env_list, saved_std);
    return (exit_status);
}

int left_pipe(t_ast *node, t_list *env_list, int saved_std[2])
{
    t_ast   *travel;
    int     exit_status;

    travel = node;
    while (is_pipe(travel->left->token->token) == 1)
	{
		travel = travel->left;
	}
    exit_status = pipe_chain(redo_env(env_list), travel->left, env_list, saved_std);
    while (travel != node)
    {
        exit_status = pipe_chain(redo_env(env_list), travel->right, env_list, saved_std);
		travel = travel->daddy;
    }
    exit_status = last_pipe(redo_env(env_list), node->right, 1, env_list, saved_std);
	
    return (exit_status);
}



int	pipe_chain(char **env, t_ast *command, t_list *env_list, int saved_std[2])
{
	int	fd[2];
	int	id;
	int	exit_status;

	if (pipe(fd) == -1)
		handle_error(-1, "pipe");
	id = fork();
	handle_error(id, "fork");
	if (id == 0)
	{
		do_pipe_redirections(command, fd, saved_std);
		exec_command(build_command(command), env, env_list);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(id, &exit_status, 0);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
	}
	return (exit_status);
}
