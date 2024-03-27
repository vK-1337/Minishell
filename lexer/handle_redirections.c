/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:33:32 by udumas            #+#    #+#             */
/*   Updated: 2024/03/27 06:16:18 by vda-conc         ###   ########.fr       */
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

int	ft_redirections(t_token **listed_tokens, t_list **env)
{
	int	status;

	status = ft_open_solo_fd(listed_tokens, env);
	if (status == -1 || status == -1917)
		return (status);
	status = ft_open_fd(listed_tokens);
	if (status == -1917)
		return (ft_tokenlstclear(listed_tokens), ft_end_minishell(env), -1917);
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
		if (curr->type == OPERATOR && curr->file_redir && ft_no_command(curr))
		{
			status = handle_fd(curr, tokens);
			update_token_link(curr);
			if (status == -1917)
				return (ft_clean_tokens(tokens), -1917);
			if (status != 0)
				return (status);
			curr = curr->next;
		}
		else
			curr = curr->next;
	}
	return (0);
}

int	export_and_wildcard2(t_token *token, t_list *env_list)
{
	char	*tmp;

	tmp = ft_strdup(token->file_redir);
	token->file_redir = ft_expand(token->file_redir, &env_list);
	ft_replace_wildcards(&token->file_redir);
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
		if (export_and_wildcard2(curr, *env) == -1)
			return (ft_clean_tokens(tokens), -1);
		fd = file_redir(curr);
		if (fd == -1917)
			return (ft_end_minishell(env), ft_clean_tokens(tokens), -1917);
		if (fd == -1)
			return (handle_error(fd, curr->file_redir), ft_clean_tokens(tokens),
				-1);
		close(fd);
		ft_tokenlstdelone(&curr);
		curr = tmp;
	}
	*tokens = curr;
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
		fd = launch_here_doc(token->file_redir, (int[2]){0, 1});
		if (fd == -1)
			return (-1917);
	}
	return (fd);
}
