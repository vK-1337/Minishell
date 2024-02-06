/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:36:48 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/06 21:01:21 by vda-conc         ###   ########.fr       */
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
char *ft_expand(char *input, t_list **env)
{
  int i;
  int *vars;
  int vars_number;
  char *final_input;
  int var_idx;

  vars_number = ft_contain_variables(input);
  if (vars_number > 0)
  {
    i = 0;
    var_idx = 0;
    vars = ft_is_expandable(input, vars_number);
    while (input[i])
    {
      if (input[i] != 36)
        final_input = ft_char_join(final_input, input[i]);
      else if (input[i] == 36 && ft_isalpha(input[i + 1]))
      {
        if (var_idx < vars_number && vars[var_idx] == 1)
        {
          if (ft_var_exists(env, &input[i]))
            final_input = ft_join_var(env, final_input, &input[i]); // TODO
          else
            final_input = ft_char_join(final_input, ' '); // ! SEE IN BASH WHAT HAPPENS IF EXPAND EMPTY VAR //
          // ! GO TO NEXT WORD ANYWAY
          while (input[i + 1] && input[i + 1] != ' ')
            i++;
        }
        else
          final_input = ft_char_join(final_input, input[i]);
        var_idx++;
      }
      i++;
    }
  }
  else
    return (input);
  return (final_input);
}

char *ft_join_var(t_list **env, char *final_input, char *input) // ! REFACTO NEEDED
{
  char *new_str;
  t_list *env_var;
  int var_len;
  int i;
  int j;

  i = 0;
  env_var = ft_find_var(env, input);
  while (((char *)env_var->content)[i])
  {
    if (((char *)env_var->content)[i] == '=')
      break;
    i++;
  }
  var_len = ft_strlen(env_var->content + i);
  new_str = malloc((ft_strlen(final_input) + var_len + 1) * sizeof(char));
  if (!new_str)
    return (NULL);
  j = 0;
  while (final_input[i])
  {
    new_str[j] = final_input[j];
    j++;
  }
  j = 0;
  while (((char *)env_var->content)[i])
  {
    new_str[j] = ((char *)env_var->content)[i];
    j++;
    i++;
  }
  new_str[j] = '\0';
  free(final_input);
  return (new_str);
}

t_list *ft_find_var(t_list **env, char* input)
{
  int i;
  t_list *curr;

  i = 0;
  while (input[i])
  {
    if (input[i] == '=')
      break;
    i++;
  }
  curr = *env;
  while (curr)
  {
    if (ft_strncmp(curr->content, input, i) == 0)
      return (curr);
    curr = curr->next;
  }
  return (NULL);
}
