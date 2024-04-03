/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:28:00 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/03 17:29:32 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	exec_built_in(char **command, t_list **env_list, char *brut_input,
		t_ast *ast)
{
	int	exit_status;

	exit_status = 1871;
	if (!command)
		return (-1917);
	if (ft_strcmp("env", command[0]) == 0)
		exit_status = ft_print_env(*env_list);
	else if (ft_strcmp("unset", command[0]) == 0)
		exit_status = ft_unset(env_list, &command[1]);
	else if (ft_strcmp("export", command[0]) == 0)
		exit_status = ft_export(env_list, ft_export_split(brut_input, ' '));
	else if (ft_strcmp("echo", command[0]) == 0)
		exit_status = ft_echo(command, brut_input, ast);
	else if (ft_strcmp("cd", command[0]) == 0)
		cd_management(command, &exit_status, env_list);
	else if (ft_strcmp("pwd", command[0]) == 0)
		exit_status = ft_pwd();
	return (ft_free_char_tab(command), exit_status);
}
