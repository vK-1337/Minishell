/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirections_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 04:03:47 by udumas            #+#    #+#             */
/*   Updated: 2024/03/28 04:24:04 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_next_prev(t_token **temp2, t_token **curr)
{
	(*temp2)->next = *curr;
	(*curr)->prev = *temp2;
	*temp2 = *curr;
	*curr = (*curr)->next;
}

void	manage_next_prev2(t_token **temp2, t_token **command)
{
	while ((*command) && ((*command)->type != COMMAND
			&& (*command)->type != PARENTHESIS))
		(*command) = (*command)->next;
	if (*temp2 && (*command) && *temp2 != (*command))
	{
		(*temp2)->next = (*command);
		(*command)->prev = *temp2;
	}
}

void	small_loop(t_token **curr)
{
	while ((*curr)->next != NULL)
		*curr = (*curr)->next;
}

int	special_loop(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if ((curr->type != OPERATOR) || !curr->file_redir)
			return (1);
		curr = curr->next;
	}
	return (0);
}
