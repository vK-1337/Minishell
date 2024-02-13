/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:45:40 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/13 09:45:49 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	**ft_unset(t_list **env_list, char *var_to_del)
{
	t_list	*curr;

	curr = *env_list;
	while (curr)
	{
		if (strncmp(curr->var_name, var_to_del, ft_strlen(var_to_del)) == 0)
		{
			if (curr->prev == NULL)
			{
				env_list = &curr->next;
				return (env_list);
			}
			else if (curr->next == NULL)
				return (ft_delete_last(curr), env_list);
			else
				return (ft_delete_connect(curr), env_list);
		}
		curr = curr->next;
	}
	return (NULL);
}
