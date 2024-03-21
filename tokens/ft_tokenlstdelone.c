/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlstdelone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 23:46:41 by vk                #+#    #+#             */
/*   Updated: 2024/03/21 11:28:36 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_tokenlstdelone(t_token **lst)
{
	if (!lst)
		return ;
	free((*lst)->token);
	free((*lst)->file_redir);
	free((*lst));
}
