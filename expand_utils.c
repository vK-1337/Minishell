/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:53:14 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/06 19:01:59 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_char_join(char *base_str, char to_join)
{
  size_t i;
  char *new_str;

  if (!base_str || !to_join)
    return (NULL);
  new_str = malloc((ft_strlen(base_str) + 2) * sizeof (char));
  if (!new_str)
    return (NULL);
  i = -1;
  while (base_str[++i])
    new_str[i] = base_str[i];
  new_str[i + 1] = to_join;
  new_str[i + 2] = '\0';
  free(base_str);
  return (new_str);
}