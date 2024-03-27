/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:56:17 by udumas            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/27 06:00:14 by vda-conc         ###   ########.fr       */
=======
/*   Updated: 2024/03/27 06:12:46 by udumas           ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_here_doc(t_ast *ast)
{
	t_token	*token;

	if (ast == NULL)
		return ;
	token = ast->token->file_redir_in;
	ast->here_doc = 0;
	while (token)
	{
		if (is(token->token, "<<") == 1)
			ast->here_doc = 1;
		token = token->next;
	}
	check_here_doc(ast->left);
	check_here_doc(ast->right);
}
int	launch_ast(char *input, t_list **env_list, int *exit_status)
{
	t_ast	*ast;
	t_token	*lexer;

	ast = NULL;
	if (!env_list)
		return (-1917);
	lexer = ft_lexer(input, env_list);
	if (!lexer)
		return (-1917);
	if (lexer && lexer->type == ERROR)
	{
		free(lexer);
        lexer = NULL;
		*exit_status = -1917;
	}
	if (create_ast_list(&ast, lexer) == NULL)
		return (-1917);
	if (!ast)
	{
		free(lexer);
		printf("Memory error\n");
		*exit_status = -1917;
	}
	check_here_doc(ast);
	launch_ast_recursive(ast, env_list, exit_status);
	ft_free_ast(&ast);
	free(lexer);
	return (*exit_status);
}

int	launch_ast_recursive(t_ast *ast, t_list **env_list, int *exit_status)
{
	export_and_wildcard(ast, *env_list);
	if (ast == NULL)
		return (0);
	else if (ast->token->type == PARENTHESIS)
		parenthesis(ast, env_list, exit_status);
	else if (is(ast->token->token, "&&") == 1 && launch_ast_recursive(ast->left,
			env_list, exit_status) == 0)
		launch_ast_recursive(ast->right, env_list, exit_status);
	else if (is(ast->token->token, "||") == 1 && launch_ast_recursive(ast->left,
			env_list, exit_status) != 0)
		launch_ast_recursive(ast->right, env_list, exit_status);
	else if (ast->token->type == 3 && is(ast->token->token, "|") == 1)
		*exit_status = create_redirection(ast, env_list);
	else if (ast->token->type == 0)
		*exit_status = exec_shell_command(ast, env_list, redo_env(*env_list),
				ast);
	return (*exit_status);
}

int	create_redirection(t_ast *node, t_list **env_list)
{
	int		exit_status;
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->saved_fd[0] = dup(0);
	exec->saved_fd[1] = dup(1);
	exec->last = 0;
	if (node->left->token->type == OPERATOR && is(node->left->token->token,
			"|") == 1)
		exit_status = left_pipe(node, env_list, &exec);
	else if (node->right->token->type == OPERATOR
		&& is(node->right->token->token, "|") == 1)
		exit_status = right_pipe(node, env_list, &exec);
	else
	{
		exit_status = pipe_chain(redo_env(*env_list), node->left, env_list,
				&exec);
		if (ft_find_var(env_list, "$?")->should_end == 1)
		{
			close(exec->fd[0]);
			close(exec->fd[1]);
			return (ft_close_fd(exec->saved_fd), free(exec), exit_status);
		}
		exit_status = last_pipe(redo_env(*env_list), node->right, env_list,
				&exec);
		if (ft_find_var(env_list, "$?")->should_end == 1)
		{
			free(exec);
			return (ft_close_fd(exec->saved_fd), exit_status);
		}
	}
	dup2(exec->saved_fd[0], 0);
	dup2(exec->saved_fd[1], 1);
	return (ft_close_fd(exec->saved_fd), free(exec), exit_status);
}
