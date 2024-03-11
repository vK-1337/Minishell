/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:51:47 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/09 13:43:54 by udumas           ###   ########.fr       */
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
		free((*list)->var_name);
		free((*list)->content);
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
