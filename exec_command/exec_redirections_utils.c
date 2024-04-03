/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:42:39 by udumas            #+#    #+#             */
/*   Updated: 2024/04/03 17:26:40 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_fd(int *fd_in)
{
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

int	ft_in_redirections(t_ast *command, t_exec **exec, t_list **env_list)
{
	t_token	*travel;

	travel = command->token->file_redir_in;
	while (travel->next)
	{
		if (configure_fd_in3((*exec)->fd[0], travel->token,
				travel->file_redir) == -1)
			return (-1);
		if (ft_strncmp(travel->token, "<<", 2) == 0)
		{
			if (launch_here_doc(travel->file_redir, (*exec)->saved_fd,
					*env_list) == -1)
				return (-1);
		}
		travel = travel->next;
	}
	(*exec)->fd[0] = c_fd_in((*exec)->fd[0], travel->token,
			travel->file_redir);
	if (ft_strcmp(travel->token, "<<") == 0)
	{
		(*exec)->fd[0] = launch_here_doc(travel->file_redir, (*exec)->saved_fd,
				*env_list);
		return (-1);
	}
	return ((*exec)->fd[0]);
}

int	ft_in_redir_o1(int *fd, t_token *travel_in, int saved_fd[2],
		t_list *env_list)
{
	*fd = c_fd_in(*fd, travel_in->token, travel_in->file_redir);
	if (ft_strncmp(travel_in->token, "<<", 2) == 0)
	{
		*fd = launch_here_doc(travel_in->file_redir, saved_fd, env_list);
		if (*fd == -1)
			return (-1917);
	}
	if (*fd == -1)
		return (-1);
	return (*fd);
}
