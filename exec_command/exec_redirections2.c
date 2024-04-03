/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:45:10 by udumas            #+#    #+#             */
/*   Updated: 2024/04/03 18:04:44 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	configure_fd_out2(int fd_out, char *token, char *file)
{
	if (file[ft_strlen(file) - 1] == ' ')
		file[ft_strlen(file) - 1] = '\0';
	if (is(token, ">") == 1)
	{
		fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (is(token, ">>") == 1)
		fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	handle_error(fd_out, file);
	if (fd_out == -1)
		return (-1);
	close(fd_out);
	return (fd_out);
}

int	do_redirection2(t_ast *command, int *fd_in, int *fd_out)
{
	t_token	*trav;

	if (command->token->file_redir_out != NULL)
	{
		trav = command->token->file_redir_out;
		while (trav->next)
		{
			if (configure_fd_out2(*fd_out, trav->token, trav->file_redir) == -1)
				return (-1);
			trav = trav->next;
		}
		*fd_out = configure_fd_out(*fd_out, trav->token, trav->file_redir);
		if (*fd_out == -1)
			return (-1);
	}
	replace_fd(fd_in);
	return (0);
}

int	do_redirectionsorder(t_ast *command, int saved_fd[2], int fd[2],
		t_list *env_list)
{
	t_token	*travel_in;
	t_token	*travel_out;
	int		count;

	initialize_redir_order(command, &travel_in, &travel_out, &count);
	while (travel_in || travel_out)
	{
		if (travel_in && (travel_in->order == count))
		{
			if (!travel_in->next)
				fd[0] = ft_in_redir_o1(&fd[0], travel_in, saved_fd, env_list);
			else
				fd[0] = ft_in_redir_o2(fd[0], travel_in, saved_fd, env_list);
			if (fd[0] == -1917)
				return (-1917);
			else if (fd[0] == -1)
				return (-1);
			travel_in = travel_in->next;
		}
		if (travel_out && (travel_out->order == count++))
			if (ft_out_redirections_order(&fd[1], &travel_out) == -1917)
				return (-1);
	}
	return (replace_fd(&fd[0]), 0);
}

void	close_exec(t_exec **exec)
{
	if ((*exec)->fd[0] != -1 && (*exec)->fd[0] != -1917)
		close((*exec)->fd[0]);
	if ((*exec)->fd[1] != -1 && (*exec)->fd[1] != -1917)
		close((*exec)->fd[1]);
	close((*exec)->saved_fd[0]);
	close((*exec)->saved_fd[1]);
	free(*exec);
}

int	do_redirections(t_ast *command, t_list *env_list)
{
	t_exec	*exec;
	int		temp;

	init_exec(&exec);
	if (command->token->file_redir_in != NULL
		&& command->token->file_redir_out != NULL)
	{
		temp = do_redirectionsorder(command, exec->saved_fd, exec->fd,
				env_list);
		if (temp == -1917)
			temp = -1;
		return (close_exec(&exec), temp);
	}
	if (command->token->file_redir_in != NULL)
	{
		if (ft_in_redirections(command, &exec, &env_list) == -1)
			return (close_exec(&exec), -1);
	}
	if (do_redirection2(command, &exec->fd[0], &exec->fd[1]) == -1)
		return (close_exec(&exec), -1);
	return (ft_close_fd(exec->saved_fd), free(exec), 0);
}
