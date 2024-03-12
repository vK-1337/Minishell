/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:29:04 by udumas            #+#    #+#             */
/*   Updated: 2024/03/12 12:05:03 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	send_to_build(t_ast **node, int direction)
{
	t_token	*strongest;

	if (direction == 1)
		strongest = get_first_strongest_operator((*node)->token);
	else
		strongest = get_last_strongest_operator((*node)->token);
	if (!strongest)
		return ;
	if (!build_tree(node, strongest))
		return ;
	send_to_build(&((*node)->right), 1);
	send_to_build(&((*node)->left), 2);
}

t_ast	*build_tree(t_ast **node, t_token *strongest)
{
	if (!strongest)
		return (NULL);
	(*node)->token = strongest;
	(*node)->left = init_branch(*node, strongest->prev, 1);
	(*node)->right = init_branch(*node, strongest->next, 0);
	if (!(*node)->left || !(*node)->right)
		return (NULL);
	return (*node);
}
