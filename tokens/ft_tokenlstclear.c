/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlstclear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 23:52:20 by vk                #+#    #+#             */
/*   Updated: 2024/02/12 19:55:56 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_tokenlstclear(t_token **lst, void (*del)(void *))
{
	t_token	*current;
	t_token	*next;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		ft_tokenlstdelone(current, del);
		current = next;
	}
	(*lst) = NULL;
}
