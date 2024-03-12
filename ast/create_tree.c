/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:25:41 by udumas            #+#    #+#             */
/*   Updated: 2024/03/12 11:39:31 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast	*init_branch(t_ast *parent, t_token *token, int is_left)
{
	t_ast	*branch;

	branch = malloc(sizeof(t_ast));
	if (!branch)
		return (NULL);
	branch->token = token;
	branch->daddy = parent;
	branch->left = NULL;
	branch->right = NULL;
	if (is_left)
	{
		while (token && token->prev)
			token = token->prev;
		if (token)
			token->next = NULL;
	}
	else if (token)
		token->prev = NULL;
	return (branch);
}

t_ast	*new_tree(t_token *strongest)
{
	t_ast	*tree;

	if (!strongest)
		return (NULL);
	tree = malloc(sizeof(t_ast));
	if (!tree)
		return (NULL);
	tree->token = strongest;
	tree->daddy = NULL;
	tree->left = init_branch(tree, strongest->prev, 1);
	tree->right = init_branch(tree, strongest->next, 0);
	if (!tree->left || !tree->right)
	{
		free(tree->left);
		free(tree->right);
		free(tree);
		return (NULL);
	}
	return (tree);
}

void	*create_ast_list(t_ast **node, t_token *token_list)
{
	t_token	*strongest;

	if (!token_list)
		return (NULL);
	strongest = get_last_strongest_operator(token_list);
	if (!strongest)
	{
		*node = malloc(sizeof(t_ast));
		if (!*node)
			return (NULL);
		(*node)->token = token_list;
		(*node)->daddy = NULL;
		(*node)->left = NULL;
		(*node)->right = NULL;
		return ((void *)1);
	}
	*node = new_tree(strongest);
	if (!*node)
		return (NULL);
	send_to_build(&((*node)->right), 1);
	send_to_build(&((*node)->left), 2);
	return ((void *)1);
}
