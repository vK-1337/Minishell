/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:08:15 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/15 16:45:52 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/home/vda-conc/Documents/Projects/Minishell/libft/libft.h"
#include <stdio.h>

void	ft_swapback_nodes(t_list *prev, t_list *curr)
{
	t_list	*prev_tmp;
	t_list	*next_tmp;

	next_tmp = curr->next;
	prev_tmp = prev->prev;
	curr->next = prev;
	curr->prev = prev_tmp;
	if (prev->prev)
		prev->prev->next = curr;
	prev->next = next_tmp;
	prev->prev = curr;
}

void	ft_print_node_list(t_list *node1)
{
	t_list	*curr;

	curr = node1;
	while (curr)
	{
		printf("Node => |%p|\n", curr);
		printf("Node.content => |%s|\n", curr->content);
		printf("Node.next => |%p|\n", curr->next);
		printf("Node.prev => |%p|\n\n", curr->prev);
		curr = curr->next;
	}
}

int	main(int ac, char **av)
{
	t_list node1;
	t_list node2;
	t_list node3;

	node1.content = "1";
	node1.next = &node2;
	node1.prev = NULL;

	node2.content = "2";
	node2.next = &node3;
	node2.prev = &node1;

	node3.content = "3";
	node3.prev = &node2;
	node3.next = NULL;

	ft_print_node_list(&node1);
	ft_swapback_nodes(&node2, &node3);
	ft_print_node_list(&node1);
	ft_swapback_nodes(&node1, &node3);
	ft_print_node_list(&node3);
	return (0);
}