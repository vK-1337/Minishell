/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:13:42 by vk                #+#    #+#             */
/*   Updated: 2024/02/08 15:26:19 by vda-conc         ###   ########.fr       */
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
    new_node->var_name = split[0];
    new_node->content = split[1];
  }
  new_node->next = NULL;
  new_node->prev = NULL;
	return (new_node);
}
