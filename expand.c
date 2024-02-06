/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:36:48 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/06 17:32:30 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_contain_variables(char *input)
{
  int i;
  int variable_count;

  i = 0;
  variable_count = 0;
  while (input[i])
  {
    if (input[i] == '$' && ft_isalpha(input[i + 1]))
      variable_count++;
    i++;
  }
  return (variable_count);
}

int *ft_is_expandable(char *input, int variable_count)
{
  int i;
  int index;
  int single_quotes;
  int double_quotes;
  int *expand_infos;

  i = 0;
  index = 0;
  single_quotes = 0;
  double_quotes = 0;
  expand_infos = malloc((variable_count) * sizeof (int));
  while (input[i])
  {
    if (input[i] == 39 && double_quotes == 0)
      single_quotes += ft_decr_incr(single_quotes);
    else if (input[i] == 34 && single_quotes == 0)
      double_quotes += ft_decr_incr(double_quotes);
    else if (input[i] == 36 && ft_isalpha(input[i + 1]))
    {
      expand_infos[index] = ft_should_expand(single_quotes, double_quotes);
      index++;
    }
    i++;
  }
  return (expand_infos);
}

int ft_decr_incr(int condition)
{
  if (condition == 1)
    return (-1);
  else if (condition == 0)
    return (1);
  return (1337);
}

int ft_should_expand(int single_quotes, int double_quotes)
{
  if (double_quotes == 0 && single_quotes == 0)
    return (1);
  else if (double_quotes == 1 && single_quotes == 0)
    return (1);
  else if (double_quotes == 0 && single_quotes == 1)
    return (0);
  return (1337);
}
ft_expand(char *input)
{
  char *final_input;

  
}