/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:53:39 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/11 15:01:32 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_reunite_tokens(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	while (curr)
	{
		if (should_join_export(curr))
		{
			ft_join_export(tokens, curr->next, curr->next->next);
			curr = *tokens;
		}
		else if (should_join_options(curr))
		{
			ft_join_options(tokens, curr, curr->next);
			curr = *tokens;
		}
		else if (should_join_file_path(curr))
		{
			ft_join_file_path(curr, curr->next);
			update_next_token_type(curr);
			curr = *tokens;
		}
		else
			curr = curr->next;
	}
	return ((void *)1);
}

int	should_join_export(t_token *curr)
{
	return (curr->next && curr->next->next && curr->type == COMMAND
		&& strncmp(curr->token, "export", 6) == 0);
}

int	should_join_options(t_token *curr)
{
	return (curr->next && curr->type == OPTION && curr->next->type == OPTION);
}

int	should_join_file_path(t_token *curr)
{
	return (curr->next && curr->type == OPERATOR
		&& curr->next->type == PATH_FILE);
}

void	update_next_token_type(t_token *curr)
{
	t_token	*next;

	next = curr->next;
	if (next->next && next->next->type == CMD_ARG)
		next->next->type = COMMAND;
}
