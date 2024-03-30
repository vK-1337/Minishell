/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:51:38 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/29 19:53:56 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_end_minishell(t_list **env_list)
{
	t_list	*ft_exit_variable;

	ft_exit_variable = ft_find_var(env_list, "$?");
	ft_exit_variable->should_end = 1;
	return ;
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '-' && str[i] != '+'
			&& str[i] != ' ' && str[i] != '"')
			return (0);
		i++;
	}
	return (1);
}

t_list	*ft_exit_variable(void)
{
	t_list	*exit_variable;

	exit_variable = malloc(sizeof(t_list));
	if (!exit_variable)
		return (NULL);
	exit_variable->var_name = ft_strdup("?");
	exit_variable->content = ft_strdup("0");
	exit_variable->env_print = 0;
	exit_variable->next = NULL;
	exit_variable->prev = NULL;
	exit_variable->xit_status = 0;
	exit_variable->should_end = 0;
	return (exit_variable);
}
