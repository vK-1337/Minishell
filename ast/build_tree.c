/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:29:04 by udumas            #+#    #+#             */
/*   Updated: 2024/03/30 12:51:30 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	send_to_build(t_ast **node, int direction)
{
	t_token	*strongest;
	t_ast	*tree;

	if (direction == 1)
	{
		strongest = get_first_strongest_operator((*node)->token);
		if (strongest == NULL)
			return ;
		tree = build_tree(node, strongest);
		send_to_build(&(tree->right), 1);
		send_to_build(&(tree->left), 2);
	}
	else if (direction == 2)
	{
		strongest = get_last_strongest_operator((*node)->token);
		if (strongest == NULL)
			return ;
		tree = build_tree(node, strongest);
		send_to_build(&(tree->right), 1);
		send_to_build(&(tree->left), 2);
	}
}

void	nullize_tree(t_ast **node, t_ast **left, t_ast **right)
{
	(*node)->left = *left;
	(*node)->right = *right;
	(*left)->daddy = *node;
	(*right)->daddy = *node;
	(*left)->left = NULL;
	(*left)->right = NULL;
	(*right)->left = NULL;
	(*right)->right = NULL;
}

t_ast	*build_tree(t_ast **node, t_token *strongest)
{
	t_ast	*left;
	t_ast	*right;

	left = malloc(sizeof(t_ast) * 1);
	right = malloc(sizeof(t_ast) * 1);
	if (!left || !right)
		return (NULL);
	(*node)->token = strongest;
	strongest->prev->next = NULL;
	strongest->next->prev = NULL;
	left->token = strongest->prev;
	strongest->prev = NULL;
	while (left->token && left->token->prev)
		left->token = left->token->prev;
	right->token = strongest->next;
	strongest->next = NULL;
	while (right->token && right->token->prev)
		right->token = right->token->prev;
	nullize_tree(node, &left, &right);
	return (*node);
}
