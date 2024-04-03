/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:56:24 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/02 17:12:51 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_manage_fd(t_exec *exec)
{
	if (exec->fd[0] == -1 || exec->fd[1] == -1)
		return (-1917);
	if (exec->fd[0] != -1000)
	{
		dup2(exec->fd[0], 0);
		close(exec->fd[0]);
	}
	if (exec->last == 1 && exec->fd[1] == -1000)
		dup2(exec->saved_fd[1], 1);
	else
	{
		if (dup2(exec->fd[1], 1) == -1)
			perror("dup2");
		close(exec->fd[1]);
	}
	return (0);
}

int	ft_utils_fd2(t_token *token, t_exec **exec)
{
	while (token->next)
	{
		if (configure_fd_out2((*exec)->fd[1], token->token,
				token->file_redir) == -1)
			return (-1917);
		close((*exec)->fd[1]);
		token = token->next;
	}
	(*exec)->fd[1] = configure_fd_out((*exec)->fd[1], token->token,
			token->file_redir);
	if ((*exec)->fd[1] == -1)
		return (-1917);
	return (0);
}
