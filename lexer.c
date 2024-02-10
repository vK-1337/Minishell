/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:34:27 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/10 19:18:29 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *ft_lexer(char *input, t_list **env)
{
  char *expanded_input;
  char **tokens;
  // t_list *listed_tokens;

  expanded_input = ft_expand(input, env);
  tokens = ft_token_split(expanded_input);
  free(expanded_input);
  ft_print_tokens(tokens);
  // listed_tokens = ft_convert_tokens(tokens);
  return (NULL);
}

// t_list *ft_convert_tokens(char **tokens)
// {
//   int i;
//   t_ttype type;
//   t_list *token_list;

//   i = 0;
//   while (tokens[i])
//   {
//     type = ft_define_ttype(tokens[i])

//   }
// }

// t_ttype ft_define_ttype(char *token)
// {
//   int i;

//   i = 0;
//   if (!token)
//     return (NULL);
//   while (token[i])
//   {
//     if (ft_is_operator(token[i]))
//       i++;
//   }
// }

int ft_is_operator(char c)
{
  if (c == 38 || c == 60 || c == 62 || c == 124)
    return (1);
  return (0);
}