/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:35:32 by udumas            #+#    #+#             */
/*   Updated: 2024/04/02 18:02:57 by udumas           ###   ########.fr       */
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
		if (curr->file_redir_in != NULL)
			free(curr->file_redir_in);
		if (curr->file_redir_out != NULL)
			free(curr->file_redir_out);
		free(curr->token);
		free(curr);
		curr = tmp;
	}
	*tokens = NULL;
	return (curr);
}

int	handle_fd(t_token *curr, t_token **tokens, t_list *env)
{
	int		fd;
	t_token	*tmp;

	fd = file_redir(curr, env);
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

t_token	*update_token_link(t_token *curr)
{
	t_token	*travel;
	t_token	*tmp;

	travel = curr;
	while (travel && travel->type == OPERATOR && travel->file_redir == NULL)
	{
		tmp = travel->next;
		free(travel->token);
		free(travel);
		travel = tmp;
	}
	if (travel && travel == curr)
	{
		travel = travel->next;
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
int		ft_no_command(t_token *token);
void	small_loop(t_token **curr);

void	ft_clean_operator(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	while ((*tokens)->type == OPERATOR && (*tokens)->file_redir != NULL
		&& ft_no_command(*tokens))
	{
		curr = (*tokens)->next;
		ft_tokenlstdelone(tokens);
		*tokens = curr;
		(*tokens)->prev = NULL;
	}
	if ((*tokens)->type == OPERATOR && (*tokens)->file_redir == NULL)
	{
		curr = (*tokens)->next;
		ft_tokenlstdelone(tokens);
		*tokens = curr;
		(*tokens)->prev = NULL;
	}
	small_loop(&curr);
	if (curr->type == OPERATOR && curr->file_redir == NULL)
	{
		curr = curr->prev;
		ft_tokenlstdelone(&curr->next);
		curr->next = NULL;
	}
}
