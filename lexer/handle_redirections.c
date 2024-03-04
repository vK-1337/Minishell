/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:33:32 by udumas            #+#    #+#             */
/*   Updated: 2024/03/04 17:33:52 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_front(t_token **command)
{
	t_token *curr;
	t_token *temp;
	
	curr = (*command)->next;
	while (curr->type == OPERATOR && (is_fd_in(curr->token) == 1 || is_fd_out(curr->token) == 1))
	{
		if (is_fd_in(curr->token) == 1)
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
		(*command)->next = curr;
		if (curr == NULL)
			break ;
	}	
}

void	ft_back(t_token **command)
{
	t_token *curr;
	t_token *temp;
	
	curr = (*command)->prev;
	while (curr->type == 3 && (is_fd_in(curr->token) == 1 || is_fd_out(curr->token) == 1))
	{
		if (is_fd_in(curr->token) == 1)
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
}
void	ft_reunite_redirection(t_token **tokens)
{
	t_token *curr;
	t_token	*temp;
	
	curr = *tokens;
	while (curr)
	{
		if (curr->type == COMMAND)
		{
			if (curr->next != NULL)
				ft_front(&curr);
			if (curr->prev != NULL)
			{
				temp = curr->prev;
				while (temp->type != 0 && temp->prev != NULL)
				{
					printf("temp->token = %s\n", temp->token);
					temp = temp->prev;
				}
					
				if (temp->prev == NULL && temp->type != COMMAND)
					*tokens = curr;
				ft_back(&curr);
			}
		}
		curr = curr->next;
	}
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