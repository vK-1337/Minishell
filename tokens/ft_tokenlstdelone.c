/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlstdelone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 23:46:41 by vk                #+#    #+#             */
/*   Updated: 2024/03/27 21:51:56 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_tokenlstdelone(t_token **lst)
{
	if (!lst || !*lst)
		return ;
	if ((*lst)->token)
		free((*lst)->token);
	if ((*lst)->file_redir)
		free((*lst)->file_redir);
	if ((*lst)->file_redir_in)
		free((*lst)->file_redir_in);
	if ((*lst)->file_redir_out)
		free((*lst)->file_redir_out);
	free((*lst));
}
