/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlstdelone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 23:46:41 by vk                #+#    #+#             */
/*   Updated: 2024/03/27 08:25:32 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_tokenlstdelone(t_token **lst)
{
	if (!lst)
		return ;
	free((*lst)->token);
	free((*lst)->file_redir);
    free((*lst)->file_redir_in);
    free((*lst)->file_redir_out);
	free((*lst));
}
