/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:51:41 by udumas            #+#    #+#             */
/*   Updated: 2024/03/12 11:26:44 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_token *token);
void	free_ast_right(t_ast *ast);

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

int	is(char *token, char *comp)
{
	if (ft_strcmp(token, comp) == 0)
		return (1);
	return (0);
}

// void	read_ast(t_ast *node, int depth)
// {
// 	t_token	*token;
// 	int		i;
// 	t_token	*temp;

// 	for (int i = 0; i < depth; i++)
// 	{
// 		printf("  ");
// 	}
// 	if (node == NULL)
// 	{
// 		printf("NULL\n");
// 		return ;
// 	}
// 	token = node->token;
// 	printf("Token: %s\n", token->token);
// 	token = token->next;
// 	i = 0;
// 	while (token != NULL)
// 	{
// 		if (token->token != NULL)
// 		{
// 			printf("    ");
// 			printf("arg%d: %s\n", i, token->token);
// 		}
// 		token = token->next;
// 		i++;
// 	}
// 	temp = node->token->file_redir_in;
// 	i = 0;
// 	while (temp != NULL)
// 	{
// 		printf("    ");
// 		printf("file_redir_in%d: %s\n", i, temp->token);
// 		printf("file_redir : %s\n", temp->file_redir);
// 		temp = temp->next;
// 		i++;
// 	}
// 	temp = node->token->file_redir_out;
// 	i = 0;
// 	while (temp != NULL)
// 	{
// 		printf("    ");
// 		printf("file_redir_out%d: %s\n", i, temp->token);
// 		printf("file_redir : %s\n", temp->file_redir);
// 		temp = temp->next;
// 		i++;
// 	}
// 	read_ast(node->left, depth + 1);
// 	read_ast(node->right, depth + 1);
// }