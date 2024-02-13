/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 23:23:30 by vk                #+#    #+#             */
/*   Updated: 2024/02/12 19:12:29 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_tokenlstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}
