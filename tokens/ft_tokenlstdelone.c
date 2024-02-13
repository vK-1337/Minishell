/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 23:46:41 by vk                #+#    #+#             */
/*   Updated: 2024/02/12 19:13:51 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_tokenlstdelone(t_token *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		del(lst->token);
	free(lst);
}
