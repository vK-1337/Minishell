/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:04:26 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/14 17:41:55 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_replace_var(t_list **env_list, char *new_var)
{
	t_list	*curr;
	int		i;

	i = 0;
	curr = *env_list;
	while (new_var[i])
	{
		if (new_var[i] == '=')
			break ;
		i++;
	}
	while (curr)
	{
		if (strncmp(curr->var_name, new_var, i) == 0
			&& curr->var_name[i] == '\0')
		{
			curr->content = ft_strdup(new_var + i + 1);
			return ;
		}
		curr = curr->next;
	}
}

void	ft_display_export(t_list **env_list)
{
	t_list	*curr;
	t_list	**list_copy;
	t_list	**sorted_list;

	list_copy = ft_copy_env_list(env_list);
	if (!list_copy)
		return ;
	ft_print_list(list_copy);
	sorted_list = ft_sort_nodes(list_copy);
	curr = *sorted_list;
	while (curr)
	{
		if (curr->content)
			printf("declare -x %s=\"%s\"\n", curr->var_name, curr->content);
		else if (curr->var_name[0] == '?')
		{
			curr = curr->next;
			continue ;
		}
		else
			printf("declare -x %s\n", curr->var_name);
		curr = curr->next;
	}
}

void	ft_print_list(t_list **env_list)
{
	t_list	*curr;

	curr = *env_list;
	while (curr)
	{
		printf("var_name: %s\n", curr->var_name);
		printf("content: %s\n", curr->content);
		curr = curr->next;
	}
}
