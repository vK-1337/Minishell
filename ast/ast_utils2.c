/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:30:08 by udumas            #+#    #+#             */
/*   Updated: 2024/03/12 12:06:09 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*get_last_strongest_operator(t_token *token_list)
{
	t_token	*strongest;
	t_token	*travel;

	strongest = NULL;
	travel = token_list;
	while (travel)
	{
		if (travel->type == 3)
		{
			if (is(travel->token, "&&") || is(travel->token, "||"))
				strongest = travel;
			else if (!strongest || (!is(travel->token, "&&")
					&& !is(travel->token, "||")))
			{
				if (!strongest || (is(travel->token, "|")
						&& is(strongest->token, "|")))
					strongest = travel;
				else if (!strongest || (!is(travel->token, "|")
						&& !is(strongest->token, "|")))
					strongest = travel;
			}
		}
		travel = travel->next;
	}
	return (strongest);
}

t_token	*get_first_strongest_operator(t_token *token_list)
{
	t_token	*strongest;
	t_token	*travel;

	strongest = NULL;
	travel = token_list;
	while (travel)
	{
		if (travel->type == 3)
			return (travel);
		travel = travel->next;
	}
	return (strongest);
}

char	*build_command(t_ast *node)
{
	t_token	*travel;
	char	*command;

	travel = node->token;
	command = ft_strdup(node->token->token);
	if (!command)
		return (NULL);
	travel = travel->next;
	while (travel != NULL)
	{
		command = ft_strjoin(command, " ", 1);
		command = ft_strjoin(command, travel->token, 1);
		if (!command)
			return (NULL);
		travel = travel->next;
	}
	return (command);
}

int	do_pipe_redirections(t_ast *command, int fd[2], int saved_std[2])
{
	t_token	*travel;

	travel = command->token->file_redir_in;
	while (travel)
	{
		fd[0] = configure_fd_in(fd[0], travel->token, travel->file_redir);
		if (ft_strncmp(travel->token, "<<", 2) == 0)
			fd[0] = launch_here_doc(travel->file_redir, saved_std);
		if (fd[0] == -1)
			return (-1917);
		travel = travel->next;
	}
	travel = command->token->file_redir_out;
	while (travel)
	{
		fd[1] = configure_fd_out(fd[1], travel->token, travel->file_redir);
		travel = travel->next;
	}
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	return (0);
}

void	export_and_wildcard(t_ast *ast, t_list *env_list)
{
	t_token	*travel;

	if (ast == NULL)
		return ;
	travel = ast->token;
	while (travel)
	{
		travel->token = ft_expand(travel->token, &env_list);
		travel = travel->next;
	}
	if (ast->token->file_redir_in)
	{
		travel = ast->token->file_redir_in;
		while (travel)
		{
			travel->file_redir = ft_expand(travel->file_redir, &env_list);
			travel = travel->next;
		}
	}
	if (ast->token->file_redir_out)
	{
		travel = ast->token->file_redir_out;
		while (travel)
		{
			travel->file_redir = ft_expand(travel->file_redir, &env_list);
			travel = travel->next;
		}
	}
	export_and_wildcard(ast->left, env_list);
	export_and_wildcard(ast->right, env_list);
}
