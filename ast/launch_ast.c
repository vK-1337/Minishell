/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:56:17 by udumas            #+#    #+#             */
/*   Updated: 2024/02/21 11:58:34 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int launch_ast(char *input, t_list *env_list)
{
    int exit_status;
    t_ast   *ast;
    
    create_ast_list(ast, ft_lexer(input, env_list)) ;
    if (!ast)
    {
        printf("Memory error\n");
        return (-1);
    }
    exit_status = launch_ast_recursive(ast, env_list);
    return (exit_status);
}

int launch_ast_recursive(t_ast *ast, t_list *env_list)
{
    t_ast *travel;
    int exit_status;
    
    exit_status = launch_ast(ast->left, env_list);
    if (ast == NULL)
        return (0);
    else if (is_and(ast->token->token) && exit_status == 0)
        exit_status = launch_ast(ast->right, env_list);
    else if (is_or(ast->token->token) && exit_status != 0)
        exit_status = launch_ast(ast->right, env_list);
    else if (ast->token->type == 3)
        exit_status = launch_redirection(ast, env_list);
    else
        exit_status = exec_command(ast, env_list);
    return (exit_status);
}

