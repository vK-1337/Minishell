/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:12:42 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/22 12:20:24 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_handle_operator_path_file(t_token **tokens, t_token *curr,
		t_token *next)
{
	ft_join_file_path(curr, next);
	return (*tokens);
}

void	*ft_join_export(t_token **tokens, t_token *curr, t_token *next)
{
	char	*new_token;
	t_token	*new_node;

	new_token = ft_strjoin(curr->token, next->token, 1);
	if (!new_token)
		return (NULL);
	new_node = ft_tokenlstnew(new_token, COMMAND);
	if (!new_node)
		return (NULL);
	new_node->next = next->next;
	if (curr->prev)
	{
		curr->prev->next = new_node;
		new_node->prev = curr->prev;
	}
	else
		*tokens = new_node;
	free(curr);
	free(next);
	return ((void *)1);
}

void	*ft_join_options(t_token **tokens, t_token *curr, t_token *next)
{
	char	*new_token;
	t_token	*new_node;

	new_token = ft_strjoin(curr->token, " ", 0);
	new_token = ft_strjoin(new_token, next->token, 1);
	if (!new_token)
		return (NULL);
	new_node = ft_tokenlstnew(new_token, OPTION);
	if (!new_node)
		return (NULL);
	new_node->next = next->next;
	if (curr->prev)
	{
		curr->prev->next = new_node;
		new_node->prev = curr->prev;
	}
	else
		*tokens = new_node;
	free(curr);
	free(next);
	return ((void *)1);
}

void	ft_join_file_path(t_token *curr, t_token *next)
{
	if (!next)
		return ;
	curr->file_redir = next->token;
	curr->next = next->next;
	if (next->next)
		next->next->prev = curr;
	free(next);
	next = NULL;
}
