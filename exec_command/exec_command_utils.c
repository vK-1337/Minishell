/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:01:49 by udumas            #+#    #+#             */
/*   Updated: 2024/03/28 00:19:41 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_built_in(t_ast *command, char **command_str, int *exit_status,
		t_list **env_list)
{
	if (command->token->token == NULL)
		return (0);
	*command_str = build_command(command);
	*exit_status = 1871;
	*exit_status = manage_built_in(ft_split(*command_str, ' '), env_list,
			*command_str, command);
    return (1);
}
