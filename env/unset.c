/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:45:40 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/01 13:43:12 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_list **env_list, char *var_to_del)
{
	t_list	*curr;

	curr = *env_list;
	if (!var_to_del)
		return (0);
	if (var_to_del[0] == '?')
		return (0);
	while (curr)
	{
		if (strncmp(curr->var_name, var_to_del, ft_strlen(var_to_del)) == 0)
		{
			if (curr->prev == NULL)
			{
				*env_list = curr->next;
				return (ft_delete_last(curr), 0);
			}
			else if (curr->next == NULL)
				return (ft_delete_last(curr), 0);
			else
				return (ft_delete_connect(curr), 0);
		}
		curr = curr->next;
	}
	return (0);
}
