/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:12:14 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/12 18:28:29 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_and_wc_helper2(t_token *travel, t_list *env_list)
{
	while (travel)
	{
		travel->file_redir = ft_expand(travel->file_redir, &env_list);
		ft_replace_wildcards(&travel->file_redir);
		travel = travel->next;
	}
}

void	export_and_wc_helper(t_token *travel, t_list *env_list)
{
	while (travel)
	{
		travel->token = ft_expand(travel->token, &env_list);
		ft_replace_wildcards(&travel->token);
		travel = travel->next;
	}
}

void	ft_add_front(t_token **command, t_token **curr)
{
	t_token	*temp;

	if ((*curr)->prev)
	{
		temp = (*curr)->prev;
		ft_tokenlstadd_front(&(*command)->file_redir_out, *curr);
		*curr = temp;
	}
	else
	{
		ft_tokenlstadd_front(&(*command)->file_redir_out, *curr);
		*curr = NULL;
	}
}
