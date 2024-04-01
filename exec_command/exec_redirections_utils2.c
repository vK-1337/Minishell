/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:53:37 by udumas            #+#    #+#             */
/*   Updated: 2024/04/01 18:13:34 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	configure_fd_in2(int fd_in, char *token, char *file)
{
	if (file[ft_strlen(file) - 1] == ' ')
		file[ft_strlen(file) - 1] = '\0';
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

int	ft_in_redir_o2(int fd, t_token *travel_in, int saved_fd[2],
		t_list *env_list)
{
	if (configure_fd_in2(fd, travel_in->token, travel_in->file_redir) == -1)
		return (-1917);
	if (ft_strncmp(travel_in->token, "<<", 2) == 0)
	{
		if (launch_here_doc(travel_in->file_redir, saved_fd, env_list) == -1)
			return (-1917);
	}
	return (fd);
}

int	ft_out_redirections_order(int *fd, t_token **travel_out)
{
	if (!(*travel_out)->next)
	{
		*fd = configure_fd_out(*fd, (*travel_out)->token,
				(*travel_out)->file_redir);
		if (*fd == -1)
			return (-1917);
	}
	else
	{
		if (configure_fd_out2(*fd, (*travel_out)->token,
				(*travel_out)->file_redir) == -1)
			return (-1917);
	}
	(*travel_out) = (*travel_out)->next;
	return (*fd);
}

int	ft_compare_limiter(char *line, char *limiter)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] != '\n')
		i++;
	line[i] = '\0';
	if (is(line, limiter) == 0)
	{
		line[i] = '\n';
		return (0);
	}
	line[i] = '\n';
	return (1);
}
