/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:40:05 by udumas            #+#    #+#             */
/*   Updated: 2024/03/27 01:57:19 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc(char *limiter, int fd[2])
{
	char	*line;
    ft_here_doc_signal_child();
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0, 1);
        if (!line)
        {
    		ft_putstr_fd("\nminishell: warning: here-document delimited by end-of-file (wanted `", 1);
            ft_putstr_fd(limiter, 1);
            ft_putstr_fd("')\n", 1);
            close(fd[1]);
			close(fd[0]);
			get_next_line(0, 0);
            break;
        }
		else if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			close(fd[1]);
			close(fd[0]);
			get_next_line(0, 0);
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}

int	launch_here_doc(char *limiter, int saved_std[2])
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
		here_doc(limiter, fd);
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
	if (is(token, "<") == 1)
		fd_in = open(file, O_RDWR, 0777);
	handle_error(fd_in, file);
	return (fd_in);
}

int	configure_fd_out(int fd_out, char *token, char *file)
{
	if (fd_out != 0 && fd_out != -1000)
		close(fd_out);
	if (is(token, ">") == 1)
	{
		fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (is(token, ">>") == 1)
		fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	handle_error(fd_out, file);
	return (fd_out);
}
