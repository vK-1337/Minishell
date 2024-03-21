/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlstclear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 23:52:20 by vk                #+#    #+#             */
/*   Updated: 2024/03/21 11:06:15 by udumas           ###   ########.fr       */
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
		printf("current->token = %s\n", current->token);
		next = current->next;
		ft_tokenlstdelone(&current);
		current = next;
	}
	(*lst) = NULL;
}
