/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:51:47 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/06 14:05:53 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list(t_list **list)
{
	t_list	*tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
}

void	ft_delete_last(t_list *env_node)
{
	env_node->prev->next = NULL;
	free(env_node);
}

void	ft_delete_connect(t_list *env_node)
{
	env_node->prev->next = env_node->next;
	env_node->next->prev = env_node->prev;
	free(env_node);
}
