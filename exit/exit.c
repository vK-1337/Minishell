/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:44 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/01 15:57:13 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(char **command, t_list **env_list)
{
	int		exit_status;
	char	*exit_status_str;

	exit_status = ft_find_var(env_list, "$?")->xit_status;
	exit_status_str = NULL;
	if (command[1] != NULL && command[2] == NULL)
	{
		exit_status = ft_atoi(command[1]);
		exit_status_str = ft_itoa(exit_status);
		if (ft_isnumber(command[1]) == 0 || (ft_strcmp(exit_status_str,
					command[1]) != 0 && command[1][0] != '+'))
			return (ft_print_error_exit(command[1], exit_status_str),
				ft_free_char_tab(command), ft_end_minishell(env_list), 2);
		ft_exit_status_helper(&exit_status);
	}
	else if (ft_tablen(command) > 2)
	{
		if (ft_istab_digits(&command[1]))
			return (ft_free_char_tab(command), printf("exit\n"),
				ft_putstr_fd("minishell: exit: too many arguments\n",
					STDERR_FILENO), 1);
		return (ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO), ft_free_char_tab(command),
			ft_end_minishell(env_list), 1);
	}
	return (printf("exit\n"), ft_free_char_tab(command),
		ft_end_minishell(env_list), free(exit_status_str), exit_status);
}

void	ft_print_error_exit(char *command, char *exit_status_str)
{
	printf("exit\n");
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	ft_putstr_fd(" numeric argument required\n", STDERR_FILENO);
	free(exit_status_str);
	return ;
}

void	ft_exit_status_helper(int *exit_status)
{
	if (*exit_status > 255 || *exit_status < -255)
		*exit_status = *exit_status % 256;
	if (*exit_status < 0)
		*exit_status = (256 + *exit_status) % 256;
}
