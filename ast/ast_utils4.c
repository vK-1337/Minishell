/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:35:37 by udumas            #+#    #+#             */
/*   Updated: 2024/03/30 12:58:44 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_manage_fd2(t_exec *exec)
{
	if (exec->fd[0] != 0)
	{
		dup2(exec->fd[0], 0);
		close(exec->fd[0]);
	}
	if (exec->last == 1 && exec->fd[1] == 1)
		dup2(exec->saved_fd[1], 1);
	else
	{
		dup2(exec->fd[1], 1);
		close(exec->fd[1]);
	}
	return (0);
}

int	wxs(int id, int *exit_status)
{
	waitpid(id, exit_status, 0);
	close(0);
	while (wait(NULL) > 0)
		continue ;
	*exit_status = *exit_status >> 8;
	return (*exit_status);
}

int	exit_pc(t_ast *command, t_exec **exec, int id)
{
	if (command->here_doc == 1)
		waitpid(id, NULL, 0);
	close((*exec)->fd[1]);
	dup2((*exec)->fd[0], 0);
	close((*exec)->fd[0]);
	return (-1);
}

void	initialize_fd_ast(int fd[2], t_ast **ast)
{
	fd[0] = dup(0);
	fd[1] = dup(1);
	*ast = NULL;
}

void	init_exec(t_exec **exec)
{
	*exec = malloc(sizeof(t_exec));
	(*exec)->saved_fd[0] = dup(0);
	(*exec)->saved_fd[1] = dup(1);
	(*exec)->fd[0] = 0;
	(*exec)->fd[1] = 1;
	(*exec)->last = 0;
}
