/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 23:26:06 by vk                #+#    #+#             */
/*   Updated: 2024/02/12 19:59:51 by vda-conc         ###   ########.fr       */
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
