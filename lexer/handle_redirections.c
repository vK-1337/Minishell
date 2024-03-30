/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:33:32 by udumas            #+#    #+#             */
/*   Updated: 2024/03/29 15:09:20 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redirections(t_token **listed_tokens, t_list **env)
{
	int	status;

	status = ft_open_solo_fd(listed_tokens, env);
	if (status == -1 || status == -1917)
		return (status);
	status = ft_open_fd(listed_tokens, *env);
	if (status == -1917)
		return (ft_tokenlstclear(listed_tokens), ft_end_minishell(env), -1917);
	if (check_only_operator(listed_tokens) == 1)
		return (-1);
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

int	ft_open_fd(t_token **tokens, t_list *env)
{
	t_token	*curr;
	int		status;
	t_token	*tmp;

	tmp = *tokens;
	curr = *tokens;
	while (curr)
	{
		if (curr->type == OPERATOR && curr->file_redir && ft_no_command(curr))
		{
			status = handle_fd(curr, tokens, env);
			if (status == -1917)
				return (ft_tokenlstclear(tokens), -1917);
			if (status != 0)
				return (ft_tokenlstclear(tokens), status);
		}
		curr = curr->next;
	}
	*tokens = tmp;
	return (0);
}

int	export_and_wildcard2(t_token *token, t_list *env_list)
{
	char	*tmp;

	tmp = ft_strdup(token->file_redir);
	if (is(token->file_redir, "<<") == 1)
	{
		token->file_redir = ft_expand(token->file_redir, &env_list);
		ft_replace_wildcards(&token->file_redir);
	}
	if (!token->file_redir)
	{
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(" :no such file or directory\n", 2);
		return (free(tmp), -1);
	}
	return (free(tmp), 0);
}

int	ft_open_solo_fd(t_token **tokens, t_list **env)
{
	t_token	*curr;
	t_token	*tmp;
	int		fd;

	if (special_loop(*tokens) == 1)
		return (1);
	curr = *tokens;
	while (curr)
	{
		tmp = curr->next;
		if (export_and_wildcard2(curr, *env) == -1)
			return (ft_clean_tokens(tokens, NULL), -1);
		fd = file_redir(curr, *env);
		if (fd == -1917)
			return (ft_end_minishell(env), ft_clean_tokens(tokens, NULL),
				-1917);
		if (fd == -1)
			return (handle_error(fd, curr->file_redir), ft_clean_tokens(tokens,
					NULL), -1);
		close(fd);
		ft_tokenlstdelone(&curr);
		curr = tmp;
	}
	*tokens = curr;
	return (-1);
}
