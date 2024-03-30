/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_utils2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 04:16:32 by udumas            #+#    #+#             */
/*   Updated: 2024/03/28 04:19:44 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_redir(t_token *token, t_list *env)
{
	char	*file;
	int		fd;

	fd = 0;
	file = token->file_redir;
	if (is(token->token, ">") == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (is(token->token, ">>") == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (is(token->token, "<") == 1)
		fd = open(file, O_RDWR, 0777);
	else if (is(token->token, "<<") == 1)
	{
		fd = launch_here_doc(token->file_redir, (int [2]){0, 1}, env);
		if (fd == -1)
			return (-1917);
	}
	return (fd);
}

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
