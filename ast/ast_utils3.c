/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:12:14 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/12 14:13:08 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_and_wc_helper(t_token *travel, t_list *env_list)
{
	while (travel)
	{
		travel->file_redir = ft_expand(travel->file_redir, &env_list);
		travel = travel->next;
	}
}

void	export_and_wc_helper2(t_token *travel, t_list *env_list)
{
	while (travel)
	{
		travel->file_redir = ft_expand(travel->file_redir, &env_list);
		travel = travel->next;
	}
}
