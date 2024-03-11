/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:13:42 by vk                #+#    #+#             */
/*   Updated: 2024/03/11 16:01:41 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, int build_env, int env_print)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	initialize_node(new_node, content, build_env, env_print);
	return (new_node);
}

void	initialize_node(t_list *node, void *content, int build_env,
		int env_print)
{
	if (!build_env)
	{
		node->var_name = NULL;
		node->content = content;
	}
	else
		init_node_env_variables(node, content);
	if (env_print)
		node->env_print = 1;
	else
		node->env_print = 0;
	node->xit_status = 0;
	node->next = NULL;
	node->prev = NULL;
}

void	*init_node_env_variables(t_list *node, void *content)
{
	int	i;
	int	j;

	i = ft_find_equal(content);
	node->var_name = malloc((i + 1) * sizeof(char));
	if (!node->var_name)
		return (NULL);
	ft_strlcpy(node->var_name, content, i + 1);
	j = ft_after_equal(content);
	if (j)
	{
		node->content = malloc((j + 1) * sizeof(char));
		if (!node->content)
			return (NULL);
		ft_strlcpy(node->content, content + i + 1, j);
	}
	else
		node->content = NULL;
    return ((void *)1);
}

int	ft_find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i);
}

int	ft_after_equal(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	j = 0;
	while (str[i++])
		j++;
	return (j);
}
