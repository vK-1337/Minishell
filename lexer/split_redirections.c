/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:32:18 by udumas            #+#    #+#             */
/*   Updated: 2024/03/20 16:17:03 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void ft_print_reverse(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr->next)
		curr = curr->next;
	while (curr)
	{
		printf("token = %s\n", curr->token);
		curr = curr->prev;
	}
}
void	ft_reunite_redirection(t_token **tokens)
{
	t_token	*curr;

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

void	handle_token_addition(t_token **command, t_token **curr)
{
	t_token	*temp;

	if (is((*curr)->token, "<") == 1 || is((*curr)->token, "<<") == 1)
	{
		temp = (*curr)->next;
		ft_tokenlstadd_back(&(*command)->file_redir_in, *curr);
		*curr = temp;
	}
	else
	{
		temp = (*curr)->next;
		ft_tokenlstadd_back(&(*command)->file_redir_out, *curr);
		*curr = temp;
	}
}

void	ft_front(t_token **command)
{
	t_token	*curr;
	t_token	*temp2;
	
	curr = (*command)->next;
	while (curr && (curr->type == OPTION || curr->type == COMMAND))
		curr = curr->next;
	if (curr)
		temp2 = curr->prev;
	else
		temp2 = NULL;
	
	while (curr && curr->type == OPERATOR && (is(curr->token, "<")
			|| is(curr->token, ">") || is(curr->token, "<<") || is(curr->token,
				">>")))
	{
		handle_token_addition(command, &curr);
		if (temp2)
			temp2->next = curr;
		
	}
}

void	ft_token_addition(t_token **command, t_token **curr)
{
	t_token	*temp;

	if (is((*curr)->token, "<") == 1 || is((*curr)->token, "<<") == 1)
	{
		if ((*curr)->prev)
		{
			temp = (*curr)->prev;
			ft_tokenlstadd_front(&(*command)->file_redir_in, *curr);
			*curr = temp;
		}
		else
		{
			ft_tokenlstadd_front(&(*command)->file_redir_in, *curr);
			*curr = NULL;
		}
	}
	else
		ft_add_front (command, curr);
}

void	ft_back(t_token **command)
{
	t_token	*curr;
	t_token	*temp2;

	if ((*command)->prev->type == COMMAND || (*command)->prev->type == OPTION)
		curr = (*command);
	else
		curr = (*command)->prev;
	temp2 = curr;
	while (temp2 && ((is(temp2->token, "<") || is(temp2->token, ">")
				|| is(temp2->token, "<<") || is(temp2->token, ">>"))))
		temp2 = temp2->prev;
	while (curr && curr->type == 3 && (is(curr->token, "<") || is(curr->token, ">")
			|| is(curr->token, "<<") || is(curr->token, ">>")))
	{
		ft_token_addition(command, &curr);
		curr = curr->prev;
	}
	while ((*command)->type != COMMAND)
		(*command) = (*command)->next;
	if (temp2 && temp2 != (*command))
	{
		temp2->next = (*command);
		(*command)->prev = temp2;
	}
}
