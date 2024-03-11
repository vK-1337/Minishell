/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:33:32 by udumas            #+#    #+#             */
/*   Updated: 2024/03/11 17:46:54 by vda-conc         ###   ########.fr       */
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

int       ft_open_solo_fd(t_token **tokens)
{
	t_token	*curr;
	t_token *tmp;
	int	fd;

	curr = *tokens;
	while (curr != NULL)
	{
		if ((curr->type != OPERATOR) ||(curr->type == OPERATOR && curr->file_redir == NULL))
			return (1);
		curr = curr->next;
	}
	curr = *tokens;
	while (curr != NULL)
	{
		tmp = curr->next;
		fd = file_redir(curr);
		if (fd == -1917)
			return (-1917);
		if (fd == -1)
			return (ft_clean_tokens(*tokens), 0);
		close (fd);
		ft_tokenlstdelone(curr);
		curr = tmp;
	}
	return(0);
}

void	ft_clean_tokens(t_token *tokens)
{
	t_token	*curr;
	t_token	*tmp;

	curr = tokens;
	while (curr != NULL)
	{
		tmp = curr->next;
		if (curr->file_redir != NULL)
			free(curr->file_redir);
		free(curr->token);
		free(curr);
		curr = tmp;
	}
}

int file_redir(t_token *token)
{
	char *file;
	int	fd = 0;

	file = token->file_redir;
	if (is_fd_out(token->token) == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (is_append(token->token) == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (is_fd_in(token->token) == 1)
		fd = open(file, O_RDWR, 0777);
	else if (is_here_doc(token->token) == 0)
	{
		fd = launch_here_doc(token->file_redir, (int[2]){0, 1});
		if (fd == -1)
			return (-1917);
	}
	return (fd);

}