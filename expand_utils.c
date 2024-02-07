/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:53:14 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/07 11:39:49 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_char_join(char *base_str, char to_join)
{
  size_t i;
  char *new_str;

  if (!to_join)
    return (NULL);
  new_str = malloc((ft_strlen(base_str) + 2) * sizeof (char));
  if (!new_str)
    return (NULL);
  i = 0;
  if (base_str)
  {
    while (base_str[i])
    {
      new_str[i] = base_str[i];
      i++;
    }
  }
  new_str[i] = to_join;
  new_str[i + 1] = '\0';
  free(base_str);
  return (new_str);
}
