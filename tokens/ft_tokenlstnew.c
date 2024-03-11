/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlstnew.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:13:42 by vk                #+#    #+#             */
/*   Updated: 2024/03/09 15:21:18 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_tokenlstnew(void *content, t_ttype type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->token = content;
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
    new_node->file_redir = NULL;
	new_node->file_redir_in = NULL;
	new_node->file_redir_out = NULL;
	new_node->fd[0] = 0;
	new_node->fd[1] = 1;
	return (new_node);
}
