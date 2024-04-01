/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:45:10 by udumas            #+#    #+#             */
/*   Updated: 2024/04/01 18:19:11 by udumas           ###   ########.fr       */
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
	replace_fd(fd_out, fd_in);
	return (0);
}

int	do_redirectionsorder(t_ast *command, int saved_fd[2], int fd[2],
		t_list *env_list)
{
	t_token	*travel_in;
	t_token	*travel_out;
	int		count;

	count = 1;
	travel_in = command->token->file_redir_in;
	travel_out = command->token->file_redir_out;
	while (travel_in || travel_out)
	{
		if (travel_in && (travel_in->order == count))
		{
			if (!travel_in->next)
				ft_in_redir_o1(&fd[0], travel_in, saved_fd, env_list);
			else
				fd[0] = ft_in_redir_o2(fd[0], travel_in, saved_fd, env_list);
			if (fd[0] == -1917 || fd[0] == -1)
				return (-1);
			travel_in = travel_in->next;
		}
		if (travel_out && (travel_out->order == count++))
			if (ft_out_redirections_order(&fd[1], &travel_out) == -1917)
				return (-1);
	}
	replace_fd(&fd[1], &fd[0]);
	return (0);
}

int	do_redirections(t_ast *command, int saved_fd[2], t_list *env_list)
{
	t_token	*travel;
	int		fd_o;
	int		fd_in;

	fd_o = 1;
	fd_in = 0;
	if (command->token->file_redir_in != NULL
		&& command->token->file_redir_out != NULL)
		return (do_redirectionsorder(command, saved_fd, (int [2]){fd_in, fd_o},
			env_list));
	if (command->token->file_redir_in != NULL)
	{
		travel = ft_in_redirections(command, fd_in, saved_fd, &env_list);
		if (travel == NULL)
			return (-1);
		fd_in = configure_fd_in(fd_in, travel->token, travel->file_redir);
		if (ft_strncmp(travel->token, "<<", 2) == 0)
			fd_in = launch_here_doc(travel->file_redir, saved_fd, env_list);
		if (fd_in == -1)
			return (-1);
	}
	if (do_redirection2(command, &fd_in, &fd_o) == -1)
		return (-1);
	return (0);
}
