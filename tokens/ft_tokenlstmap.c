/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlstmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:07 by vk                #+#    #+#             */
/*   Updated: 2024/03/11 20:34:05 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_tokenlstmap(t_token *lst, void *(*f)(void *), void (*del)(void *))
{
	t_token	*new;
	t_token	*new_head;

	if (!f || !del)
		return (NULL);
	new_head = NULL;
	while (lst != NULL)
	{
		new = ft_tokenlstnew(f(lst->token), 0);
		if (!new)
		{
			ft_tokenlstclear(&new);
			return (NULL);
		}
		ft_tokenlstadd_back(&new_head, new);
		lst = lst->next;
	}
	return (new_head);
}
