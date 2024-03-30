/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:12:14 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/29 23:25:49 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_and_wc_helper2(t_token *travel, t_list *env_list)
{
	while (travel)
	{
		if (is(travel->token, "<<") == 0)
		{
			travel->file_redir = ft_expand(travel->file_redir, &env_list);
			ft_replace_wildcards(&travel->file_redir);
		}
		travel = travel->next;
	}
}

void	export_and_wc_helper(t_token *travel, t_list *env_list)
{
	while (travel)
	{
		travel->token = ft_expand(travel->token, &env_list);
		ft_replace_wildcards(&travel->token);
		travel = travel->next;
	}
}

void	ft_add_front(t_token **command, t_token **curr)
{
	t_token	*temp;

	if ((*curr)->prev)
	{
		temp = (*curr)->prev;
		ft_tokenlstadd_front(&(*command)->file_redir_out, *curr);
		*curr = temp;
	}
	else
	{
		ft_tokenlstadd_front(&(*command)->file_redir_out, *curr);
		*curr = NULL;
	}
}

int	configure_fd_in3(int fd_in, char *token, char *file)
{
	if (is(token, "<") == 1)
		fd_in = open(file, O_RDWR, 0777);
	handle_error(fd_in, file);
	if (fd_in == -1)
		return (-1);
	close(fd_in);
	return (fd_in);
}

int	ft_utils_fd(t_token *travel, t_exec **exec, t_list *env)
{
	while (travel->next)
	{
		if (configure_fd_in3((*exec)->fd[0], travel->token,
				travel->file_redir) == -1)
			return (-1917);
		if (ft_strncmp(travel->token, "<<", 2) == 0)
		{
			if (launch_here_doc(travel->file_redir, (*exec)->saved_fd, env)
				== -1)
				return (-1917);
		}
		travel = travel->next;
	}
	(*exec)->fd[0] = configure_fd_in((*exec)->fd[0], travel->token,
			travel->file_redir);
	if (ft_strcmp(travel->token, "<<") == 0)
		(*exec)->fd[0] = launch_here_doc(travel->file_redir, (*exec)->saved_fd,
				env);
	if ((*exec)->fd[0] == -1)
		return (-1917);
	dup2((*exec)->fd[0], 0);
	close((*exec)->fd[0]);
	return (0);
}
