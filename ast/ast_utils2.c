/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:30:08 by udumas            #+#    #+#             */
/*   Updated: 2024/03/13 20:07:37 by udumas           ###   ########.fr       */
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
		if (!travel->token)
			return (command);
		command = ft_strjoin(command, travel->token, 1);
		if (!command)
			return (NULL);
		travel = travel->next;
	}
	return (command);
}

int	do_pipe_redirections(t_ast *command, t_exec **exec)
{
	t_token	*travel;
	
	travel = command->token->file_redir_in;
	while (travel)
	{
		(*exec)->fd[0] = configure_fd_in((*exec)->fd[0], travel->token,
				travel->file_redir);
		if (ft_strncmp(travel->token, "<<", 2) == 0)
			(*exec)->fd[0] = launch_here_doc(travel->file_redir,
					(*exec)->saved_fd);
		if ((*exec)->fd[0] == -1)
			return (-1917);
		travel = travel->next;
	}
	travel = command->token->file_redir_out;
	while (travel)
	{
		(*exec)->fd[1] = configure_fd_out((*exec)->fd[1], travel->token,
				travel->file_redir);
		travel = travel->next;
	}
	if ((*exec)->fd[0] != -1000)
	{
		dup2((*exec)->fd[0], 0);
		close((*exec)->fd[0]);
	}
	if ((*exec)->last == 1 && (*exec)->fd[1] == -1000)
		dup2((*exec)->saved_fd[1], 1);
	else
	{	
		dup2((*exec)->fd[1], 1);
		close((*exec)->fd[1]);
	}
	return (0);
}

void	export_and_wildcard(t_ast *ast, t_list *env_list)
{
	t_token	*travel;

	if (ast == NULL)
		return ;
	travel = ast->token;
	export_and_wc_helper(travel, env_list);
	if (ast->token->file_redir_in)
	{
		travel = ast->token->file_redir_in;
		export_and_wc_helper2(travel, env_list);
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
