/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlstclear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 23:52:20 by vk                #+#    #+#             */
/*   Updated: 2024/03/27 16:28:01 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_tokenlstclear(t_token **lst)
{
	t_token	*current;
	t_token	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	if (current->token == NULL)
	{
		free(*lst);
		*lst = NULL;
		return ;
	}
	while (current != NULL)
	{
		next = current->next;
		ft_tokenlstdelone(&current);
		current = next;
	}
	(*lst) = NULL;
}
