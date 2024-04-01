/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:32:18 by udumas            #+#    #+#             */
/*   Updated: 2024/04/01 17:31:57 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_reverse_token_list(t_token **lexer);

void	ft_reunite_redirection(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	if ((*tokens)->type != COMMAND && (*tokens)->type != PARENTHESIS)
	{
		while ((*tokens)->next && (((*tokens)->type != COMMAND)
				&& (*tokens)->type != PARENTHESIS))
			(*tokens) = (*tokens)->next;
	}
	while (curr)
	{
		if (curr->type == COMMAND || curr->type == PARENTHESIS)
		{
			if (curr->next != NULL)
				ft_front(&curr);
			if (curr->prev != NULL)
				ft_back(&curr);
			if (curr && curr->next != NULL)
				curr->next->prev = curr;
		}
		if (curr)
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
	t_token	*c;
	t_token	*temp2;

	c = (*command)->next;
	while (c && (c->type == OPTION || c->type == COMMAND
			|| c->type == PARENTHESIS))
		c = c->next;
	if (c)
		temp2 = c->prev;
	else
		temp2 = NULL;
	while (c && c->type == OPERATOR && (is(c->token, "<") || is(c->token, ">")
			|| is(c->token, "<<") || is(c->token, ">>")))
	{
		handle_token_addition(command, &c);
		if (c && (c->type == COMMAND || c->type == PARENTHESIS
				|| c->type == OPTION) && c->next)
			manage_next_prev(&temp2, &c);
		else if (temp2)
		{
			temp2->next = c;
			if (c)
				c->prev = temp2;
		}
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
		ft_add_front(command, curr);
}

void	ft_back(t_token **command)
{
	t_token	*curr;
	t_token	*temp2;

	if ((*command)->prev && ((*command)->prev->type == COMMAND
			|| (*command)->prev->type == OPTION
			|| (*command)->prev->type == PARENTHESIS))
		curr = (*command);
	else if (!(*command)->prev)
		return ;
	else
		curr = (*command)->prev;
	temp2 = curr;
	while (temp2 && ((is(temp2->token, "<") || is(temp2->token, ">")
				|| is(temp2->token, "<<") || is(temp2->token, ">>"))))
		temp2 = temp2->prev;
	while (curr && curr->type == 3 && (is(curr->token, "<") || is(curr->token,
				">") || is(curr->token, "<<") || is(curr->token, ">>")))
	{
		ft_token_addition(command, &curr);
	}
	manage_next_prev2(&temp2, command);
}
