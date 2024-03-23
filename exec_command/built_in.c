/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:01:28 by udumas            #+#    #+#             */
/*   Updated: 2024/03/23 13:23:17 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_command(char *command);

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
int manage_built_in2(char **brut_input, t_list **env_list, t_ast *ast)
{
	char	**command;
	int		exit_status;

	command = ft_split(*brut_input, ' ');
	exit_status = check_command(command[0]);
	if (exit_status == 2)
		return (free(*brut_input), ft_free_char_tab(command), ft_exit(command, env_list));
	exit_status = exec_built_in(command, env_list, *brut_input, ast);
	ft_end_minishell(env_list);
	return (free(*brut_input), exit_status);
}

int	manage_built_in(char **command, t_list **env_list, char *brut_input, t_ast *ast)
{
	int	exit_status;
	int	saved_fd[2];

	exit_status = check_command(command[0]);
	saved_fd[0] = dup(0);
	saved_fd[1] = dup(1);
	if (exit_status == 0)
		return (ft_free_char_tab(command), 1871);
    if (do_redirections(ast, saved_fd) == -1917)
	{
		dup2(saved_fd[0], 0);
		dup2(saved_fd[1], 1);
		return (1);
	}
	if (exit_status == 2)
	{
        dup2(saved_fd[0], 0);
	    dup2(saved_fd[1], 1);
        return (ft_exit(command, env_list));
	}
	exit_status = exec_built_in(command, env_list, brut_input, ast);
	dup2(saved_fd[0], 0);
	dup2(saved_fd[1], 1);
	return (close(saved_fd[0]), close(saved_fd[1]), exit_status);
}

int	check_command(char *command)
{
	if (ft_strcmp("env", command) == 0)
		return (1);
	else if (ft_strcmp("unset", command) == 0)
		return (1);
	else if (ft_strcmp("export", command) == 0)
		return (1);
	else if (ft_strcmp("exit", command) == 0)
		return (2);
	else if (ft_strcmp("echo", command) == 0)
		return (1);
	else if (ft_strcmp("cd", command) == 0)
		return (1);
	else if (ft_strcmp("pwd", command) == 0)
		return (1);
	return (0);
}

int	exec_built_in(char **command, t_list **env_list, char *brut_input, t_ast *ast)
{
	int exit_status;

	exit_status = 1871;
	if (!command)
		return (-1917);
	if (ft_strcmp("env", command[0]) == 0)
		exit_status = ft_print_env(*env_list);
	else if (ft_strcmp("unset", command[0]) == 0)
		exit_status = ft_unset(env_list, command[1]);
	else if (ft_strcmp("export", command[0]) == 0)
		exit_status = ft_export(env_list, command[1]);
	else if (ft_strcmp("echo", command[0]) == 0)
		exit_status = ft_echo(command, brut_input, ast);
	else if (ft_strcmp("cd", command[0]) == 0)
	{
		if (tablen(command) > 2)
		{
			ft_putstr_fd("cd: too many arguments\n", 2);
			exit_status = 1;
		}
		else if (command[1] == NULL)
			exit_status = ft_cd(ft_find_var(env_list, "$HOME")->content,
					env_list);
		else
			exit_status = ft_cd(command[1], env_list);
	}
	else if (ft_strcmp("pwd", command[0]) == 0)
		exit_status = ft_pwd();
	return (ft_free_char_tab(command), exit_status);
}