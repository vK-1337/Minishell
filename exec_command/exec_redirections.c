/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:40:05 by udumas            #+#    #+#             */
/*   Updated: 2024/04/03 17:00:18 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_here_doc_error(char *limiter);

void	here_doc(char *limiter, int fd[2], t_list *env_list)
{
	char	*line;

	ft_here_doc_signal_child();
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO, 1);
		if (ft_compare_limiter(line, limiter) == 0)
			line = ft_expand(line, &env_list);
		if (!line || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			if (!line)
				ft_here_doc_error(limiter);
			else
				free(line);
			close(fd[1]);
			close(fd[0]);
			get_next_line(0, 0);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}

int	launch_here_doc(char *limiter, int saved_std[2], t_list *env_list)
{
	int	fd[2];
	int	id;

	pipe(fd);
	dup2(saved_std[0], 0);
	id = fork();
	handle_error(id, "fork");
	ft_here_doc_signals();
	if (id == 0)
	{
		here_doc(limiter, fd, env_list);
		return (-1);
	}
	else
	{
		close(fd[1]);
		wait(&id);
	}
	return (fd[0]);
}

int	configure_fd_in(int fd_in, char *token, char *file)
{
	if (file[ft_strlen(file) - 1] == ' ')
		file[ft_strlen(file) - 1] = '\0';
	if (is(token, "<") == 1)
		fd_in = open(file, O_RDWR, 0777);
	handle_error(fd_in, file);
	if (fd_in == -1)
		return (-1);
	return (fd_in);
}

int	configure_fd_out(int fd_out, char *token, char *file)
{
	if (file[ft_strlen(file) - 1] == ' ')
		file[ft_strlen(file) - 1] = '\0';
	if (is(token, ">") == 1)
		fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (is(token, ">>") == 1)
		fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd_out == -1)
	{
		handle_error(fd_out, file);
		return (-1);
	}
	if (dup2(fd_out, 1) == -1)
	{
		handle_error(-1, "dup2");
		return (-1);
	}	
	close(fd_out);
	return (fd_out);
}
