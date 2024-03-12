/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:56:17 by udumas            #+#    #+#             */
/*   Updated: 2024/03/12 12:01:36 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	launch_ast(char *input, t_list *env_list, int *exit_status)
{
	t_ast	*ast;
	t_token	*lexer;

	ast = NULL;
	if (!env_list)
		return (-1917);
	lexer = ft_lexer(input, &env_list);
	if (lexer && lexer->type == ERROR)
	{
		free(lexer);
		*exit_status = -1917;
	}
	if (create_ast_list(&ast, lexer) == NULL)
		return (-1917);
	if (!ast)
	{
		printf("Memory error\n");
		*exit_status = -1917;
	}
	launch_ast_recursive(ast, env_list, exit_status);
	ft_free_ast(ast);
	return (*exit_status);
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
	else if (is(ast->token->token, "&&") == 1 && launch_ast_recursive(ast->left,
			env_list, exit_status) == 0)
		launch_ast_recursive(ast->right, env_list, exit_status);
	else if (is(ast->token->token, "||") == 1 && launch_ast_recursive(ast->left,
			env_list, exit_status) != 0)
		launch_ast_recursive(ast->right, env_list, exit_status);
	else if (ast->token->type == 3 && is(ast->token->token, "|") == 1)
		*exit_status = create_redirection(ast, env_list);
	else if (ast->token->type == 0)
	{
		env = redo_env(env_list);
		*exit_status = exec_shell_command(ast, env_list, env);
	}
	return (*exit_status);
}

int	create_redirection(t_ast *node, t_list *env_list)
{
	int	exit_status;
	int	saved_std[2];

	saved_std[0] = dup(0);
	saved_std[1] = dup(1);
	if (is(node->left->token->token, "|") == 1)
		exit_status = left_pipe(node, env_list, saved_std);
	else if (is(node->right->token->token, "|") == 1)
		exit_status = right_pipe(node, env_list, saved_std);
	else
	{
		pipe_chain(redo_env(env_list), node->left, env_list, saved_std);
		exit_status = last_pipe(redo_env(env_list), node->right, env_list,
				saved_std);
	}
	dup2(saved_std[0], 0);
	close(saved_std[0]);
	close(saved_std[1]);
	return (exit_status);
}
