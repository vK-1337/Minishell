/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:58:48 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/05 20:58:19 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_export(t_list *env_list, char *new_var)
{
  ft_lstadd_back(&env_list, ft_lstnew(new_var));
}

t_list **ft_unset(t_list **env_list, char*var_to_del)
{
  t_list *curr;

  curr = *env_list;
  while (curr)
  {
    if (strncmp(curr->content, var_to_del, ft_strlen(var_to_del)) == 0)
    {
      if (curr->prev == NULL)
      {
        env_list = &curr->next;
        return (env_list);
      }
      else if (curr->next == NULL)
      {
        curr->prev->next = NULL;
        free(curr);
        return (env_list);
      }
      else
      {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        free(curr);
        return (env_list);
      }
    }
    curr = curr->next;
  }
  return (NULL);
}
