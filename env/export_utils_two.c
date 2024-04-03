/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:04:26 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/02 18:35:32 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_replace_var(t_list **env_list, char *n)
{
	t_list	*curr;
	int		i;

	i = -1;
	curr = *env_list;
	while (n[++i])
	{
		if (n[i] == '=')
			break ;
	}
	while (curr)
	{
		if (strncmp(curr->var_name, n, i) == 0 && curr->var_name[i] == '\0')
		{
			free(curr->content);
			if (!n[i])
				curr->content = NULL;
			else if (ft_contain_equal(n))
				curr->content = ft_strdup(n + i + 1);
			else
				curr->content = ft_strdup(n + i);
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
	ft_free_list(list_copy);
	free(list_copy);
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
