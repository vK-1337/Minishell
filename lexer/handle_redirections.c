/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:33:32 by udumas            #+#    #+#             */
/*   Updated: 2024/03/19 17:40:10 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putnbr_redir(t_token **tokens)
{
	t_token	*curr;
	int		i;

	curr = *tokens;
	while (curr)
	{
		curr->order = 0;
		curr = curr->next;
	}
	i = 1;
	curr = *tokens;
	while (curr)
	{
		if (curr->type == OPERATOR && curr->file_redir != NULL)
		{
			curr->order = i;
			i++;
		}
		if (curr->type == OPERATOR && curr->file_redir == NULL)
			curr->order = 1;
		curr = curr->next;
	}
}
int	ft_redirections(t_token **listed_tokens)
{
	int	status;

	status = ft_open_solo_fd(listed_tokens);
	if (status == -1 || status == -1917)
		return (status);
	status = ft_open_fd(listed_tokens);
	if (status == -1917)
		return (-1917);
	if (check_only_operator(listed_tokens) == 1)
		return (ft_tokenlstclear(listed_tokens), -1);
	ft_clean_operator(listed_tokens);
	ft_putnbr_redir(listed_tokens);
	ft_reunite_redirection(listed_tokens);
	return (0);
}

int	ft_no_command(t_token *token)
{
	t_token	*curr;

	curr = token->prev;
	while (curr)
	{
		if (curr->type != OPERATOR)
			return (0);
		if (curr->type == OPERATOR && curr->file_redir == NULL)
			break ;
		curr = curr->prev;
	}
	curr = token->next;
	while (curr)
	{
		if (curr->type != OPERATOR)
			return (0);
		if (curr->type == OPERATOR && curr->file_redir == NULL)
			break ;
		curr = curr->next;
	}
	if (curr == NULL)
		return (1);
	return (1);
}

int	ft_open_fd(t_token **tokens)
{
	t_token	*curr;
	int		status;

	curr = *tokens;
	while (curr)
	{
		if (curr->type == OPERATOR && !curr->file_redir && ft_no_command(curr))
		{
			update_token_link(curr);
			status = handle_fd(curr, tokens);
			if (status != 0)
				return (status);
			curr = curr->next->prev;
		}
		else
			curr = curr->next;
	}
	return (0);
}

int	ft_open_solo_fd(t_token **tokens)
{
	t_token	*curr;
	t_token	*tmp;
	int		fd;

	curr = *tokens;
	while (curr)
	{
		if ((curr->type != OPERATOR) || !curr->file_redir)
			return (1);
		curr = curr->next;
	}
	curr = *tokens;
	while (curr)
	{
		tmp = curr->next;
		fd = file_redir(curr);
		if (fd == -1917)
			return (-1917);
		if (fd == -1)
			return (ft_clean_tokens(tokens), -1);
		close(fd);
		ft_tokenlstdelone(&curr);
		curr = tmp;
	}
	return (-1);
}

int	file_redir(t_token *token)
{
	char	*file;
	int		fd;

	fd = 0;
	file = token->file_redir;
	fd = 0;
	if (is(token->token, ">") == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (is(token->token, ">>") == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (is(token->token, "<") == 1)
		fd = open(file, O_RDWR, 0777);
	else if (is(token->token, "<<") == 1)
	{
		fd = launch_here_doc(token->file_redir, (int [2]){0, 1});
		if (fd == -1)
			return (-1917);
	}
	return (fd);
}
