/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:45:10 by udumas            #+#    #+#             */
/*   Updated: 2024/03/14 15:40:18 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_redirection2(t_ast *command, int *fd_in, int *fd_out)
{
	t_token	*travel;

	if (command->token->file_redir_out != NULL)
	{
		travel = command->token->file_redir_out;
		while (travel)
		{
			configure_fd_out(*fd_out, travel->token, travel->file_redir);
			travel = travel->next;
		}
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
}

int	do_redirections(t_ast *command, int saved_fd[2])
{
	t_token	*travel;
	int		fd_out;
	int		fd_in;

	fd_out = 1;
	fd_in = 0;
	if (command->token->file_redir_in != NULL)
	{
		travel = command->token->file_redir_in;
		while (travel)
		{
			fd_in = configure_fd_in(fd_in, travel->token, travel->file_redir);
			if (ft_strncmp(travel->token, "<<", 2) == 0)
				fd_in = launch_here_doc(travel->file_redir, saved_fd);
			if (fd_in == -1)
				return (-1917);
			travel = travel->next;
		}
	}
	do_redirection2(command, &fd_in, &fd_out);
	return (0);
}

void	handle_error(int err, char *msg)
{
	if (err == -1)
	{
		perror(msg);
	}
}
int ft_tablen(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}