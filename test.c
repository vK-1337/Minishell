/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:08:15 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/16 15:14:36 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/home/vda-conc/Documents/Projects/Minishell/libft/libft.h"
#include <stdio.h>
int ft_is_prev_greater(char *curr_var, char *prev_var)
{
    int i;

    i = 0;
    if (!prev_var)
        return (0);
    while (curr_var[i] && prev_var[i])
    {
        if (curr_var[i] == prev_var[i])
            i++;
        else if (prev_var[i] > curr_var[i])
            return (1);
        else
            return (0);
    }
    return (1337);
}

void	ft_swapback_nodes(t_list *prev, t_list *curr)
{
	t_list	*prev_tmp;
	t_list	*next_tmp;

	next_tmp = curr->next;
	prev_tmp = prev->prev;
    if (curr->next)
        curr->next->prev = prev;
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

t_list **ft_sort_nodes(t_list **env_list)
{
    t_list *curr;
    t_list *tmp;
    t_list *last_node;
    int i;

    curr = *env_list;
    curr = curr->next;
    i = 0;
    while (curr)
    {
        tmp = curr->next;
        while (curr->prev && ft_is_prev_greater(curr->content, curr->prev->content))
            ft_swapback_nodes(curr->prev, curr);
        curr = tmp;
        if (curr)
            last_node = curr;
    }
    curr = last_node;
    while (curr)
    {
        last_node = curr;
        curr = curr->prev;
    }
    *env_list = last_node;
    return (env_list);
}

int	main(int ac, char **av)
{
    t_list *list;
	t_list node1;
	t_list node2;
	t_list node3;
    t_list node4;
    t_list node5;
    t_list **new_list;


	node1.content = "SALUT";
	node1.next = &node2;
	node1.prev = NULL;

	node2.content = "_SALUT";
	node2.next = &node3;
	node2.prev = &node1;

	node3.content = "COUCOU";
	node3.prev = &node2;
	node3.next = &node4;

    node4.content = "BONJOUR";
    node4.next = &node5;
    node4.prev = &node3;

    node5.content = "salut";
    node5.next = NULL;
    node5.prev = &node4;

    list = &node1;
    printf("Before\n");
    ft_print_node_list(&node1);
	new_list = ft_sort_nodes(&list);
    printf("After\n");
    ft_print_node_list(*new_list);
    (void)ac;
    (void)av;
    return (0);
}