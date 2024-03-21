/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:25:41 by udumas            #+#    #+#             */
/*   Updated: 2024/03/21 15:03:12 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	nullize_tree2(t_ast **tree, t_ast **left, t_ast **right)
{
	(*right)->left = NULL;
	(*right)->right = NULL;
	(*left)->left = NULL;
	(*left)->right = NULL;
	(*tree)->token->next = NULL;
	(*tree)->token->prev = NULL;
}

t_ast	*new_tree(t_token *strongest)
{
	t_ast	*tree;
	t_ast	*left;
	t_ast	*right;

	if (strongest == NULL)
		return (NULL);
	tree = malloc(sizeof(t_ast) * 1);
	left = malloc(sizeof(t_ast) * 1);
	right = malloc(sizeof(t_ast) * 1);
	if (!tree || !left || !right)
		return (NULL);
	tree->token = strongest;
	tree->daddy = NULL;
	left->token = strongest->prev;
	left->token->next = NULL;
	while (left->token->prev != NULL)
		left->token = left->token->prev;
	tree->left = left;
	right->token = strongest->next;
	right->token->prev = NULL;
	tree->right = right;
	right->daddy = tree;
	left->daddy = tree;
	nullize_tree2(&tree, &left, &right);
	return (tree);
}

void	nullize_tree3(t_ast **node, t_token *token_list)
{
	(*node)->token = token_list;
	(*node)->daddy = NULL;
	(*node)->left = NULL;
	(*node)->right = NULL;
}

void	*create_ast_list(t_ast **node, t_token *token_list)
{
	t_token	*strongest;
	t_ast	*tree;

	if (token_list == NULL)
		return (NULL);
	if (get_last_strongest_operator(token_list) == NULL)
	{
		*node = malloc(sizeof(t_ast));
		if (*node == NULL)
			return (NULL);
		nullize_tree3(node, token_list);
	}
	else if (*node == NULL)
	{
		strongest = get_last_strongest_operator(token_list);
		tree = new_tree(strongest);
		*node = tree;
		if (tree == NULL)
			return (NULL);
		send_to_build(&(tree->right), 1);
		send_to_build(&(tree->left), 2);
	}
	return ((void *)1);
}
