/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:13:42 by vk                #+#    #+#             */
/*   Updated: 2024/03/08 12:43:38 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, int build_env, int env_print)
{
	t_list	*new_node;
	int		i;
	int		j;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	if (!build_env)
	{
		new_node->var_name = NULL;
		new_node->content = content;
	}
	else
	{
		i = ft_find_equal(content);
		new_node->var_name = malloc((i + 1) * sizeof(char));
		if (!new_node->var_name)
			return (NULL);
		ft_strlcpy(new_node->var_name, content, i + 1);
		j = ft_after_equal(content);
		if (j)
		{
			new_node->content = malloc((j + 1) * sizeof(char));
			if (!new_node->content)
				return (NULL);
			ft_strlcpy(new_node->content, content + i + 1, j);
		}
	}
	if (env_print)
		new_node->env_print = 1;
	else
		new_node->env_print = 0;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
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
	int i;
	int j;

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