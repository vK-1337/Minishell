/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:42:39 by udumas            #+#    #+#             */
/*   Updated: 2024/04/01 18:14:18 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_fd(int *fd_out, int *fd_in)
{
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

int	handle_error(int err, char *msg)
{
	if (err == -1)
	{
		perror(msg);
	}
	return (err);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

t_token	*ft_in_redirections(t_ast *command, int fd_in, int saved_fd[2],
		t_list **env_list)
{
	t_token	*travel;

	travel = command->token->file_redir_in;
	while (travel->next)
	{
		if (configure_fd_in2(fd_in, travel->token, travel->file_redir) == -1)
			return (NULL);
		if (ft_strncmp(travel->token, "<<", 2) == 0)
		{
			if (launch_here_doc(travel->file_redir, saved_fd, *env_list) == -1)
				return (NULL);
		}
		travel = travel->next;
	}
	return (travel);
}

int	ft_in_redir_o1(int *fd, t_token *travel_in, int saved_fd[2],
		t_list *env_list)
{
	*fd = configure_fd_in(*fd, travel_in->token, travel_in->file_redir);
	if (ft_strncmp(travel_in->token, "<<", 2) == 0)
		*fd = launch_here_doc(travel_in->file_redir, saved_fd, env_list);
	if (*fd == -1)
		return (-1917);
	return (*fd);
}
