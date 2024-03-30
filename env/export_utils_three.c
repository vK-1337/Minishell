/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:44:52 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/27 23:51:10 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_var_exists(t_list **env_list, char *var)
{
	t_list	*curr;
	int		i;

	curr = *env_list;
	i = 0;
	while (ft_isalnum(var[i + 1]) || var[i + 1] == '_' || var[i + 1] == '?')
		i++;
	if (var[0] == '$' || var[0] == '{')
		var++;
	else
		i++;
	if (var[0] == '?')
		return (1);
	while (curr)
	{
		if (ft_strncmp(curr->var_name, var, i) == 0
			&& curr->var_name[i] == '\0')
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
