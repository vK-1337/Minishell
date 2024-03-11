/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlstadd_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 23:26:06 by vk                #+#    #+#             */
/*   Updated: 2024/03/09 13:29:32 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_tokenlstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	tmp = NULL;
	if (!lst || !new)
		return ;
	if (*lst)
	{
		tmp = ft_tokenlstlast((*lst));
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
	{
		new->next = NULL;
		new->prev = NULL;
		*lst = new;
	}
}
