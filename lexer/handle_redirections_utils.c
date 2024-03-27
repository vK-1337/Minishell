/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:35:32 by udumas            #+#    #+#             */
/*   Updated: 2024/03/27 07:46:58 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_clean_tokens(t_token **tokens, t_token **tokens2)
{
	t_token	*curr;
	t_token	*tmp;

	if (!(*tokens))
		curr = *tokens2;
	else
		curr = *tokens;
	while (curr)
	{
		tmp = curr->next;
		if (curr->file_redir != NULL)
			free(curr->file_redir);
		free(curr->token);
		free(curr);
		curr = tmp;
	}
	*tokens = NULL;
	return (curr);
}

int	handle_fd(t_token *curr, t_token **tokens)
{
	int		fd;
	t_token	*tmp;

	fd = file_redir(curr);
	tmp = curr->next;
	if (fd == -1)
	{
		tmp->prev = ft_clean_tokens(tokens, NULL);
		tmp->prev->next = tmp;
		return (-1);
	}
	else if (fd == -1917)
		return (-1917);
	close(fd);
	return (0);
}

t_token *	update_token_link(t_token *curr)
{
	t_token *travel;
	t_token *tmp;

	travel = curr;
	while (travel && travel->type == OPERATOR && travel->file_redir == NULL)
	{
		tmp = travel->next;
		free(travel->token);
		if (travel->file_redir)
			free(travel->file_redir);
		free(travel);
		travel = tmp;
	}
	if (travel && travel == curr)
	{
		travel = travel->next;
		free(curr->token);
		if (curr->file_redir)
			free(curr->file_redir);
		free(curr);
		curr = NULL;
	}
	return (travel);
}

int	check_only_operator(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	while (curr)
	{
		if (curr->type != OPERATOR)
			return (0);
		curr = curr->next;
	}
	return (1);
}

void	ft_clean_operator(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	if ((*tokens)->type == OPERATOR && (*tokens)->file_redir == NULL)
	{
		printf("tokens->token = %s\n", (*tokens)->token);
		curr = (*tokens)->next;
		ft_tokenlstdelone(tokens);
		*tokens = curr;
		(*tokens)->prev = NULL;
	}
	while (curr->next != NULL)
		curr = curr->next;
	if (curr->type == OPERATOR && curr->file_redir == NULL)
	{
		curr = curr->prev;
		ft_tokenlstdelone(&curr->next);
		curr->next = NULL;
	}
}
