/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:33:32 by udumas            #+#    #+#             */
/*   Updated: 2024/03/08 19:28:24 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_front(t_token **command)
{
	t_token *curr;
	t_token *temp;
	t_token *temp2;
	
	curr = (*command)->next;
	while (curr && (curr->type == COMMAND || curr->type == OPTION))
		curr = curr->next;
	if (curr == NULL)
		return ;
	temp2 = curr->prev;
	while (curr && curr->type == OPERATOR && (is_fd_in(curr->token) == 1
				|| is_fd_out(curr->token) == 1 || is_here_doc(curr->token) == 1
			|| is_append(curr->token) == 1))
	{
		if (is_fd_in(curr->token) == 1 || is_here_doc(curr->token) == 1)
		{
			if (curr->next)
			{
				temp = curr->next;
				ft_tokenlstadd_back(&(*command)->file_redir_in, curr);
				curr = temp;
			}
			else
			{
				ft_tokenlstadd_back(&(*command)->file_redir_in, curr);
				curr = NULL;
			}
		}
		else
		{
			if (curr->next)
			{
				temp = curr->next;
				ft_tokenlstadd_back(&(*command)->file_redir_out, curr);
				curr = temp;
			}
			else
			{
				ft_tokenlstadd_back(&(*command)->file_redir_out, curr);
				curr = NULL;
			}
		}
		temp2->next = curr;
		if (curr == NULL)
			break ;
	}
}

void	ft_back(t_token **command)
{
	t_token *curr;
	t_token *temp;
	t_token *temp2;
	curr = (*command)->prev;
	temp2 = curr;
	while (temp2 && ((is_fd_in(temp2->token) == 1
			|| is_fd_out(temp2->token) == 1 || is_here_doc(temp2->token) == 1
		|| is_append(temp2->token) == 1)))
		temp2 = temp2->prev;
	while (curr->type == 3 && (is_fd_in(curr->token) == 1
			|| is_fd_out(curr->token) == 1 || is_here_doc(curr->token) == 1
		|| is_append(curr->token) == 1))
	{
		if (is_fd_in(curr->token) == 1 || is_here_doc(curr->token) == 1)
		{
			if (curr->prev)
			{
				temp = curr->prev;
				ft_tokenlstadd_front(&(*command)->file_redir_in, curr);
				curr = temp;
			}
			else
			{
				ft_tokenlstadd_front(&(*command)->file_redir_in, curr);
				curr = NULL;
			}
		}
		else
		{
			if (curr->prev)
			{
				temp = curr->prev;
				ft_tokenlstadd_front(&(*command)->file_redir_out, curr);
				curr = temp;
			}
			else
			{
				ft_tokenlstadd_front(&(*command)->file_redir_out, curr);
				curr = NULL;
			}
		}
		(*command)->prev = curr;
		if (curr == NULL)
			break ;
	}
	if (temp2 && temp2 != (*command))
		temp2->next = (*command);
}
void	ft_reunite_redirection(t_token **tokens)
{
	t_token *curr;
	
	curr = *tokens;
	if ((*tokens)->type != COMMAND && (*tokens)->type != PARENTHESIS)
	{
		while ((*tokens)->next && ((*tokens)->type != COMMAND))
			(*tokens) = (*tokens)->next;
	}
	while (curr)
	{
		if (curr->type == COMMAND)
		{
			if (curr->next != NULL)
				ft_front(&curr);
			if (curr->prev != NULL)
				ft_back(&curr);
			if (curr->next != NULL)
				curr->next->prev = curr;
		}
		curr = curr->next;
	}
	(*tokens)->prev = NULL;
}

void	ft_initialize_redirection(t_token **tokens)
{
	t_token *curr;

	curr = *tokens;
	while (curr)
	{
		if (curr->type == COMMAND)
		{
			curr->file_redir_in = NULL;
			curr->file_redir_out = NULL;
		}
		curr = curr->next;
	}
}