/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:45:40 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/03 19:08:30 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_list **env_list, char **var_to_del)
{
	t_list	*curr;
	int		i;

	if (!var_to_del || !var_to_del[0])
		return (0);
	i = -1;
	while (var_to_del[++i])
	{
		curr = *env_list;
		if (var_to_del[i][0] == '?')
			continue ;
		while (curr)
		{
			if (ft_strncmp(curr->var_name, var_to_del[i],
					ft_strlen(var_to_del[i])) == 0
				&& curr->var_name[ft_strlen(var_to_del[i])] == '\0')
			{
				ft_unset_helper(curr, env_list);
				break ;
			}
			curr = curr->next;
		}
	}
	return (0);
}

void	ft_unset_helper(t_list *curr, t_list **env_list)
{
	if (curr->prev == NULL)
	{
		*env_list = curr->next;
		ft_delete_last(curr);
	}
	else if (curr->next == NULL)
		ft_delete_last(curr);
	else
		ft_delete_connect(curr);
}
