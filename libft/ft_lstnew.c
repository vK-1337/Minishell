/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:13:42 by vk                #+#    #+#             */
/*   Updated: 2024/02/08 18:37:02 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, int build_env)
{
	t_list	*new_node;
  char **split;

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
    split = ft_split(content, '=');
    new_node->var_name = ft_strdup(split[0]);
    new_node->content = ft_strdup(split[1]);
    free(split);
  }
  new_node->next = NULL;
  new_node->prev = NULL;
	return (new_node);
}
