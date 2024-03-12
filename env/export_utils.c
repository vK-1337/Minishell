/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:03:42 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/12 14:03:59 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	**ft_copy_env_list(t_list **env_list)
{
	t_list	*curr;
	t_list	**copy;
	t_list	*node_copy;

	curr = *env_list;
	copy = NULL;
	while (curr)
	{
		node_copy = ft_copy_env_node(curr);
		if (!node_copy)
			return (NULL);
		ft_lstadd_back(copy, node_copy);
		curr = curr->next;
	}
	return (copy);
}

t_list	*ft_copy_env_node(t_list *env_node)
{
	t_list	*copy;

	copy = malloc(sizeof(t_list));
	if (!copy)
		return (NULL);
	copy->content = env_node->content;
	copy->var_name = env_node->var_name;
	copy->next = NULL;
	copy->prev = NULL;
	return (copy);
}

t_list	**ft_sort_nodes(t_list **env_list)
{
	t_list	*curr;
	t_list	*tmp;
	t_list	*last_node;

	curr = *env_list;
	curr = curr->next;
	while (curr)
	{
		tmp = curr->next;
		while (curr->prev && ft_is_prev_greater(curr->var_name,
				curr->prev->var_name))
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

void	ft_swapback_nodes(t_list *prev, t_list *curr)
{
	t_list	*prev_tmp;
	t_list	*next_tmp;

	next_tmp = curr->next;
	prev_tmp = prev->prev;
	if (curr->next)
	{
		curr->next->prev = prev;
	}
	curr->next = prev;
	curr->prev = prev_tmp;
	if (prev->prev)
		prev->prev->next = curr;
	prev->next = next_tmp;
	prev->prev = curr;
}

int	ft_is_prev_greater(char *curr_var, char *prev_var)
{
	int	i;

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
