/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:45:10 by udumas            #+#    #+#             */
/*   Updated: 2024/03/19 18:54:39 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	configure_fd_out2(int fd_out, char *token, char *file)
{
	if (fd_out != 0)
		close(fd_out);
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
	t_token	*travel;

	if (command->token->file_redir_out != NULL)
	{
		travel = command->token->file_redir_out;
		while (travel->next)
		{
			if (configure_fd_out2(*fd_out, travel->token, travel->file_redir) == -1)
				break ;
			travel = travel->next;
		}
		*fd_out = configure_fd_out(*fd_out, travel->token, travel->file_redir);
		if (*fd_out == -1)
			return (-1);
	}
	if (*fd_out != 1)
	{
		dup2(*fd_out, 1);
		close(*fd_out);
	}
	if (*fd_in != 0)
	{
		dup2(*fd_in, 0);
		close(*fd_in);
	}
	return (0);
}
int	configure_fd_in2(int fd_in, char *token, char *file)
{
	if (fd_in != 0)
		close(fd_in);
	else if (is(token, "<") == 1)
		fd_in = open(file, O_RDWR, 0777);
	handle_error(fd_in, file);
	if (fd_in == -1)
		return (-1);
	close(fd_in);
	return (fd_in);
}

int do_redirectionsorder(t_ast *command, int saved_fd[2], int fd_in, int fd_out)
{
	t_token *travel_in;
	t_token *travel_out;
	int count;

	count = 1;
	travel_in = command->token->file_redir_in;
	travel_out = command->token->file_redir_out;
	while (travel_in || travel_out)
	{
		if (travel_in && (travel_in->order == count))
		{
			if (!travel_in->next)
			{
				fd_in = configure_fd_in(fd_in, travel_in->token, travel_in->file_redir);
				if (ft_strncmp(travel_in->token, "<<", 2) == 0)
					fd_in = launch_here_doc(travel_in->file_redir, saved_fd);
				if (fd_in == -1)
					return (-1917);
			}
			else
			{
				if (configure_fd_in2(fd_in, travel_in->token, travel_in->file_redir) == -1)
				return (-1917) ;
				if (ft_strncmp(travel_in->token, "<<", 2) == 0)
				{
					if (launch_here_doc(travel_in->file_redir, saved_fd) == -1)
						return (-1917);
				}
			}
			travel_in = travel_in->next;
		}
		if (travel_out && (travel_out->order == count))
		{
			if (!travel_out->next)
			{
				fd_out = configure_fd_out(fd_out, travel_out->token, travel_out->file_redir);
				if (fd_out == -1)
					return (-1917);
			}
			else
			{
				if (configure_fd_out2(fd_out, travel_out->token, travel_out->file_redir) == -1)
					return (-1917);
			}
			travel_out = travel_out->next;
		}
		count++;
	}
	if (fd_out != 1)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
	if (fd_in != 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	return (0);
}
int	do_redirections(t_ast *command, int saved_fd[2])
{
	t_token	*travel;
	int		fd_out;
	int		fd_in;

	fd_out = 1;
	fd_in = 0;
	if (command->token->file_redir_in != NULL && command->token->file_redir_out != NULL)
		return (do_redirectionsorder(command, saved_fd, fd_in, fd_out));
	if (command->token->file_redir_in != NULL)
	{
		travel = command->token->file_redir_in;
		while (travel->next)
		{
			if (configure_fd_in2(fd_in, travel->token, travel->file_redir) == -1)
				return (-1917) ;
			if (ft_strncmp(travel->token, "<<", 2) == 0)
			{
				if (launch_here_doc(travel->file_redir, saved_fd) == -1)
					return (-1917);
			}
			travel = travel->next;
		}
		fd_in = configure_fd_in(fd_in, travel->token, travel->file_redir);
		if (ft_strncmp(travel->token, "<<", 2) == 0)
			fd_in = launch_here_doc(travel->file_redir, saved_fd);
		if (fd_in == -1)
			return (-1917);
	}
	if (do_redirection2(command, &fd_in, &fd_out) == -1)
		return (-1917);
	return (0);
}

void	handle_error(int err, char *msg)
{
	if (err == -1)
	{
		perror(msg);
	}
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
