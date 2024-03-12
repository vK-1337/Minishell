/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:51:41 by udumas            #+#    #+#             */
/*   Updated: 2024/03/12 17:19:50 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_token *token);
void	free_ast_right(t_ast *ast);

int is(char *token, char *comp)
{
	if (ft_strcmp(token, comp) == 0)
		return (1);
	return (0);

}
void	ft_free_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	free_ast_right(ast);
}

void	free_ast_right(t_ast *ast)
{
	t_ast	*right;
	t_ast	*left;

	while (ast != NULL)
	{
		right = ast->right;
		left = ast->left;
		if (right != NULL)
			free_ast_right(right);
		if (left != NULL)
			free_ast_right(left);
		free_token(ast->token);
		free(ast);
		ast = NULL;
	}
}

void	free_token(t_token *token)
{
	t_token	*next;

	if (token == NULL)
		return ;
	while (token != NULL)
	{
		next = token->next;
		free(token->token);
		free(token);
		token = next;
	}
	return ;
}
