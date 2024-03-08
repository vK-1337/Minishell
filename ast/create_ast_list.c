/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:25:41 by udumas            #+#    #+#             */
/*   Updated: 2024/03/06 19:07:00 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_or(char *token)
{
	if (ft_strncmp(token, "||", 2) == 0)
		return (1);
	return (0);
}

int	is_and(char *token)
{
	if (ft_strncmp(token, "&&", 2) == 0)
		return (1);
	return (0);
}

int	is_pipe(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (1);
	return (0);
}

int	is_fd_out(char *token)
{
	if (ft_strcmp(token, ">") == 0)
		return (1);
	return (0);
}

int	is_fd_in(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (1);
	return (0);
}

int is_here_doc(char *token)
{
	if (ft_strcmp(token, "<<") == 0)
		return (1);
	return (0);
}

int is_append(char *token)
{
	if (ft_strcmp(token, ">>") == 0)
		return (1);
	return (0);
}
t_token	*get_last_strongest_operator(t_token *token_list)
{
	t_token	*strongest;
	t_token	*travel;

	strongest = NULL;
	travel = token_list;
	while (travel)
	{
		if (travel->type == 3)
		{
			if (is_and(travel->token) == 1 || is_or(travel->token) == 1)
				strongest = travel;
			else
			{
				if (!strongest || (is_and(strongest->token) == 0
						&& is_or(strongest->token) == 0))
				{
					if (!strongest || (is_pipe(travel->token) == 1
							&& is_pipe(strongest->token) == 1))
						strongest = travel;
					else if (!strongest || ((is_pipe(travel->token) == 0)
							&& is_pipe(strongest->token) == 0))
						strongest = travel;
				}
			}
		}
		travel = travel->next;
	}
	return (strongest);
}

t_token	*get_first_strongest_operator(t_token *token_list)
{
	t_token	*strongest;
	t_token	*travel;

	strongest = NULL;
	travel = token_list;
	while (travel)
	{
		if (travel->type == 3)
			return (travel);
		travel = travel->next;
	}
	return (strongest);
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
	right->left = NULL;
	right->right = NULL;
	left->left = NULL;
	left->right = NULL;
	tree->token->next = NULL;
	tree->token->prev = NULL;
	return (tree);
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
	(*node)->left = left;
	(*node)->right = right;
	left->daddy = *node;
	right->daddy = *node;
	left->left = NULL;
	left->right = NULL;
	right->left = NULL;
	right->right = NULL;
	return (*node);
}

void	read_ast(t_ast *node, int depth)
{
	t_token	*token;
	int		i;

	for (int i = 0; i < depth; i++)
	{
		printf("  ");
	}
	if (node == NULL)
	{
		printf("NULL\n");
		return ;
	}
	token = node->token;
	printf("Token: %s\n", token->token);
	token = token->next;
	i = 0;
	while (token != NULL)
	{
		printf("    ");
		printf("arg%d: %s\n", i, token->token);
		token = token->next;
		i++;
	}
	t_token *temp = node->token->file_redir_in;
	i = 0;
	while (temp != NULL)
	{
		printf("    ");
		printf("file_redir_in%d: %s\n", i, temp->token);
		printf("file_redir : %s\n", temp->file_redir);
		temp = temp->next;
		i++;
	}
	temp = node->token->file_redir_out;
	i = 0;
	while (temp != NULL)
	{
		printf("    ");
		printf("file_redir_out%d: %s\n", i, temp->token);
		printf("file_redir : %s\n", temp->file_redir);
		temp = temp->next;
		i++;
	}
	read_ast(node->left, depth + 1);
	read_ast(node->right, depth + 1);
}

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
		ft_print_token_list(&(*node)->token);
		strongest = get_last_strongest_operator((*node)->token);
		if (strongest == NULL)
			return ;
		tree = build_tree(node, strongest);
		send_to_build(&(tree->right), 1);
		send_to_build(&(tree->left), 2);
	}
}

void	create_ast_list(t_ast **node, t_token *token_list)
{
	t_token	*strongest;
	t_ast	*tree;

	if (get_last_strongest_operator(token_list) == NULL)
	{
		*node = malloc(sizeof(t_ast));
		(*node)->token = token_list;
		(*node)->daddy = NULL;
		(*node)->left = NULL;
		(*node)->right = NULL;
	}
	else if (*node == NULL)
	{
		strongest = get_last_strongest_operator(token_list);
		tree = new_tree(strongest);
		*node = tree;
		if (tree == NULL)
			return ;
		send_to_build(&(tree->right), 1);
		send_to_build(&(tree->left), 2);
	}
}
